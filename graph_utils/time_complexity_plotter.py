from __future__ import annotations

import math
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Callable, Iterable

import numpy as np
from PIL import Image, ImageDraw, ImageFont


_O_EXPR_RE = re.compile(r"O\(([^)]+)\)", re.IGNORECASE)


def _extract_o_expressions_from_text(text: str) -> list[str]:
    """
    Extract every O(...) fragment from a snippet of text.
    Example: "..., O(n log n) average, O(n^2) worst" -> ["n log n", "n^2"].
    """
    expressions: list[str] = []
    start = 0
    text_lower = text.lower()

    while True:
        idx = text_lower.find("o(", start)
        if idx == -1:
            break

        depth = 0
        content_start = idx + 2
        for pos in range(idx + 1, len(text)):
            ch = text[pos]
            if ch == "(":
                depth += 1
            elif ch == ")":
                depth -= 1
                if depth == 0:
                    expressions.append(text[content_start:pos].strip())
                    start = pos + 1
                    break
        else:
            break

    return expressions


def _infer_o_expressions_from_complexity_text(complexity_text: str) -> list[str]:
    text = complexity_text.lower()

    if "exponential" in text:
        return ["2^n"]
    if "factorial" in text:
        return ["n!"]
    if "n log n" in text:
        return ["n log n"]
    if "log n" in text or "logarithmic" in text:
        return ["log n"]
    if "cubic" in text:
        return ["n^3"]
    if "quadratic" in text:
        return ["n^2"]
    if "linear" in text:
        return ["n"]
    if "constant" in text:
        return ["1"]

    return []


def extract_time_complexity_o_expressions(file_path: Path) -> list[str]:
    """
    Reads only the first ~60 lines to find a "Time Complexity" comment and extracts all O(...)
    expressions from those lines.
    """

    try:
        # Most of these files keep complexity in a short header comment.
        lines = file_path.read_text(encoding="utf-8", errors="ignore").splitlines()
    except Exception:
        return []

    relevant: list[str] = []
    for line in lines[:60]:
        if "time complexity" in line.lower():
            relevant.append(line)

    # If the file has no explicit "Time Complexity:" line, fall back to scanning the header.
    if not relevant:
        relevant = lines[:20]

    o_exprs: list[str] = []
    for line in relevant:
        o_exprs.extend(_extract_o_expressions_from_text(line))

    # De-duplicate while preserving order.
    seen: set[str] = set()
    out: list[str] = []
    for e in o_exprs:
        key = e.replace(" ", "").lower()
        if key not in seen:
            seen.add(key)
            out.append(e)
    if out:
        return out

    inferred = _infer_o_expressions_from_complexity_text(extract_time_complexity_text(file_path))
    return inferred


def _header_lines(file_path: Path, *, limit: int = 60) -> list[str]:
    try:
        return file_path.read_text(encoding="utf-8", errors="ignore").splitlines()[:limit]
    except Exception:
        return []


def extract_algorithm_title(file_path: Path) -> str:
    """
    Try to infer a friendly algorithm title from the first header comment.
    Falls back to the file stem if no descriptive header is present.
    """

    for line in _header_lines(file_path, limit=12):
        text = line.strip().lstrip("/#*").strip()
        if not text or ":" not in text:
            continue
        title = text.split(":", 1)[0].strip()
        if title:
            return title

    return file_path.stem.replace("_", " ")


def extract_time_complexity_text(file_path: Path) -> str:
    """
    Extract a human-readable time-complexity note for chart subtitles.
    """

    lines = _header_lines(file_path)
    for line in lines:
        if "time complexity" in line.lower():
            cleaned = line.strip().lstrip("/#*").strip()
            match = re.search(r"time complexity\s*:\s*(.+)$", cleaned, re.IGNORECASE)
            if match:
                value = match.group(1).strip().rstrip(".")
                if value:
                    return value
            return cleaned.rstrip(".")

    o_exprs = extract_time_complexity_o_expressions(file_path)
    if o_exprs:
        return ", ".join(f"O({expr})" for expr in o_exprs)

    return "Not specified"


def _log10_factorial(n: float) -> float:
    # log10(n!) = log10(Gamma(n+1)) and gamma grows extremely fast.
    # math.lgamma returns ln(gamma(x)).
    return math.lgamma(n + 1.0) / math.log(10.0)


def _safe_log10(x: np.ndarray) -> np.ndarray:
    # x must be > 0 for log. We only call this with n>=1.
    return np.log10(x)


def build_log10_complexity_function(o_expr: str, *, w_value: float = 100.0) -> Callable[[np.ndarray], np.ndarray]:
    """
    Convert an O(...) expression string into a function that returns log10(T(n)).

    We intentionally plot log10(time) to avoid overflows with factorial/exponential.
    """

    expr = o_expr.strip().lower().replace(" ", "")

    # Normalize a couple common variants.
    expr = expr.replace("log(n)", "logn").replace("ln(n)", "logn")
    expr = expr.replace("logv", "logn").replace("loge", "logn")
    expr = expr.replace("(v+e)", "n").replace("v+e", "n")
    expr = expr.replace("(m+n)", "n").replace("m+n", "n")
    expr = expr.replace("v^3", "n^3").replace("e^3", "n^3")
    expr = expr.replace("v", "n").replace("m", "n")
    expr = expr.replace("w", "w")

    if "e" in expr and "logn" in expr:
        expr = "n^2logn"
    elif expr == "e":
        expr = "n^2"
    else:
        expr = expr.replace("e", "n")

    def model(n: np.ndarray) -> np.ndarray:
        # Use float computations.
        n = n.astype(float)
        eps = 1e-300

        # Constant-ish.
        if expr in {"1", "constant", "const", "o(1)"}:
            return np.zeros_like(n)

        # log n
        if expr in {"logn", "log"}:
            return _safe_log10(np.maximum(np.log(n), 1.0))  # keep values defined for n>=2

        # n log n
        if expr in {"nlogn", "n*logn", "nlog(n)", "nlogn."} or ("nlogn" in expr and "n!" not in expr):
            return _safe_log10(n) + _safe_log10(np.maximum(np.log(n), 1.0))

        # n! and variants
        if "n!" in expr:
            if expr in {"n!", "n*n!"} or expr.startswith("n!*") or expr.endswith("*n!"):
                # includes n! alone (and we also handle n*n! below)
                if expr == "n!":
                    return np.vectorize(_log10_factorial)(n)
                # n*n!
                if expr == "n*n!":
                    return _safe_log10(n) + np.vectorize(_log10_factorial)(n)
            # Handle "n*n!" even when extra '*' exist
            if "n*n!" in expr:
                return _safe_log10(n) + np.vectorize(_log10_factorial)(n)

            # Unknown factorial form: approximate as n!
            return np.vectorize(_log10_factorial)(n)

        # Exponential: 2^n or 2**n
        if "2^n" in expr or "2**n" in expr:
            # detect polynomial factor n^k if present
            poly_k = 0
            m = re.search(r"n\^(\d+)", expr)
            if m:
                poly_k = int(m.group(1))
            # log10(2^n) = n * log10(2)
            y = n * math.log10(2.0)
            if poly_k:
                y = y + poly_k * _safe_log10(n)
            return y

        # Polynomials: n^k
        m_pow = re.search(r"n\^(\d+)", expr)
        if m_pow:
            k = int(m_pow.group(1))
            return k * _safe_log10(n)

        # nW: treat W as constant multiplier.
        if expr == "nw" or expr.startswith("nw") or expr.endswith("nw"):
            return _safe_log10(n) + _safe_log10(np.array([w_value]))

        # n*something linear-ish
        if expr == "n":
            return _safe_log10(n)

        # n^2*logn etc fallback heuristics
        if expr in {"n^2logn", "n2logn"}:
            return 2.0 * _safe_log10(n) + _safe_log10(np.maximum(np.log(n), 1.0))

        if "nlogn" in expr:
            return 2.0 * _safe_log10(n)  # crude fallback

        # If we can't recognize it, approximate with n^2.
        return 2.0 * _safe_log10(np.maximum(n, 1.0) + eps)

    return model


def sanitize_filename(stem: str) -> str:
    s = re.sub(r"[^a-zA-Z0-9._-]+", "_", stem).strip("._-")
    return s if s else "time_complexity"


@dataclass(frozen=True)
class PlotSpec:
    file_path: Path
    o_expressions: list[str]
    title: str
    complexity_text: str


def build_absolute_model_from_o_expr(
    o_expr: str, *, w_value: float = 100.0, absolute_scale: float = 1.0
) -> Callable[[np.ndarray], np.ndarray]:
    """
    Build a (potentially huge) absolute T(n) model from an O(...) expression.

    We still compute in log10-space internally to avoid numerical overflow, then convert back.
    The returned values are in arbitrary units (since we only have Big-O, not real benchmarks).
    """

    log10_model = build_log10_complexity_function(o_expr, w_value=w_value)

    def T(n: np.ndarray) -> np.ndarray:
        # Convert log10(T) -> T with clipping to keep finite values.
        y_log10 = log10_model(n)
        # Convert back to linear scale, but clip in log-space to avoid overflow.
        # Use a very large cap because we later may scale curves for readability.
        y_max = absolute_scale * 1e300
        y_log10_max = math.log10(y_max) if y_max > 0 else 18.0
        y_log10_clipped = np.minimum(y_log10, y_log10_max)
        y = np.power(10.0, y_log10_clipped) * absolute_scale
        return y

    return T


def _load_font(size: int, *, bold: bool = False) -> ImageFont.FreeTypeFont | ImageFont.ImageFont:
    candidates = [
        "arialbd.ttf" if bold else "arial.ttf",
        "DejaVuSans-Bold.ttf" if bold else "DejaVuSans.ttf",
    ]
    for candidate in candidates:
        try:
            return ImageFont.truetype(candidate, size)
        except OSError:
            continue
    return ImageFont.load_default()


def _draw_line_chart(
    *,
    x_values: np.ndarray,
    series: list[tuple[str, np.ndarray]],
    title: str,
    subtitle: str,
    out_path: Path,
) -> None:
    width, height = 1200, 760
    image = Image.new("RGB", (width, height), "white")
    draw = ImageDraw.Draw(image)

    title_font = _load_font(34, bold=True)
    subtitle_font = _load_font(22)
    label_font = _load_font(20)
    tick_font = _load_font(16)
    legend_font = _load_font(18)

    left, top, right, bottom = 120, 160, 1100, 620
    plot_width = right - left
    plot_height = bottom - top

    palette = [
        "#1f77b4",
        "#d62728",
        "#2ca02c",
        "#9467bd",
        "#ff7f0e",
        "#17becf",
    ]

    all_y = np.concatenate([y for _, y in series]) if series else np.array([0.0, 1.0])
    y_max = float(np.max(all_y)) if all_y.size else 1.0
    if y_max <= 0:
        y_max = 1.0

    x_min = float(x_values.min()) if x_values.size else 0.0
    x_max = float(x_values.max()) if x_values.size else 1.0
    x_range = max(x_max - x_min, 1.0)

    def px_x(x: float) -> int:
        return int(left + ((x - x_min) / x_range) * plot_width)

    def px_y(y: float) -> int:
        normalized = 0.0 if y_max == 0 else min(max(y / y_max, 0.0), 1.0)
        return int(bottom - normalized * plot_height)

    draw.text((left, 35), title, fill="black", font=title_font)
    draw.text((left, 78), subtitle, fill="#333333", font=subtitle_font)

    for i in range(6):
        frac = i / 5
        y_val = y_max * frac
        y = px_y(y_val)
        draw.line([(left, y), (right, y)], fill="#dddddd", width=1)
        tick_label = f"{y_val:.0f}" if y_max >= 10 else f"{y_val:.2f}"
        draw.text((left - 85, y - 8), tick_label, fill="#444444", font=tick_font)

    x_ticks = min(6, len(x_values)) if len(x_values) > 1 else 2
    for i in range(x_ticks):
        frac = i / max(x_ticks - 1, 1)
        x_val = x_min + frac * x_range
        x = px_x(x_val)
        draw.line([(x, top), (x, bottom)], fill="#eeeeee", width=1)
        draw.text((x - 18, bottom + 12), f"{int(round(x_val))}", fill="#444444", font=tick_font)

    draw.line([(left, top), (left, bottom)], fill="black", width=2)
    draw.line([(left, bottom), (right, bottom)], fill="black", width=2)

    for idx, (label, y_values) in enumerate(series):
        color = palette[idx % len(palette)]
        points = [(px_x(float(x)), px_y(float(y))) for x, y in zip(x_values, y_values)]
        if len(points) >= 2:
            draw.line(points, fill=color, width=3)
        elif points:
            x, y = points[0]
            draw.ellipse((x - 2, y - 2, x + 2, y + 2), fill=color, outline=color)

    draw.text((left + plot_width // 2 - 55, bottom + 45), "Input size n", fill="black", font=label_font)
    draw.text((18, top + plot_height // 2), "T(n)", fill="black", font=label_font)

    legend_x = right - 210
    legend_y = top + 10
    legend_height = 30 * max(len(series), 1) + 20
    draw.rounded_rectangle((legend_x, legend_y, right - 10, legend_y + legend_height), radius=10, outline="#cccccc", fill="#fafafa")
    for idx, (label, _) in enumerate(series):
        color = palette[idx % len(palette)]
        y = legend_y + 12 + idx * 30
        draw.line([(legend_x + 12, y + 10), (legend_x + 42, y + 10)], fill=color, width=3)
        draw.text((legend_x + 52, y), label, fill="black", font=legend_font)

    image.save(out_path)


def generate_time_complexity_plot(
    spec: PlotSpec,
    *,
    output_dir: Path,
    n_min: int = 2,
    n_max: int = 200,
    w_value: float = 100.0,
) -> Path:
    """
    Generate one PNG per code file (absolute T(n) growth).
    """

    output_dir.mkdir(parents=True, exist_ok=True)

    n = np.arange(n_min, n_max + 1, dtype=int)
    # Default to something reasonable so the graph still exists.
    o_exprs = spec.o_expressions or ["n"]

    # Compute all curves first so we can apply a single constant scale factor
    # to make the plot readable on a normal (linear) y-axis.
    y_series: list[tuple[str, np.ndarray]] = []
    for o_expr in o_exprs:
        try:
            T = build_absolute_model_from_o_expr(o_expr, w_value=w_value, absolute_scale=1.0)
            y_series.append((o_expr, T(n)))
        except Exception:
            continue

    any_curve = len(y_series) > 0
    if any_curve:
        max_y = max(float(y.max()) for _, y in y_series if y.size > 0)
        target_max = 1e6
        scale = 1.0 if max_y <= 0 or max_y <= target_max else target_max / max_y

        scaled_series = [(f"O({o_expr})", y * scale) for o_expr, y in y_series]
    else:
        # Extremely defensive fallback.
        T = build_absolute_model_from_o_expr("n^2", w_value=w_value, absolute_scale=1.0)
        y = T(n)
        max_y = float(y.max()) if y.size else 0.0
        target_max = 1e6
        scale = 1.0 if max_y <= 0 or max_y <= target_max else target_max / max_y
        scaled_series = [("O(n^2) (fallback)", y * scale)]
        any_curve = True

    if not any_curve:
        # Extremely defensive fallback.
        T = build_absolute_model_from_o_expr("n^2", w_value=w_value)
        y = T(n)
        scaled_series = [("O(n^2) (fallback)", y)]

    stem = spec.file_path.name
    if spec.file_path.suffix:
        stem = spec.file_path.stem

    filename = f"time_complexity_absolute_{sanitize_filename(stem)}.png"
    out_path = output_dir / filename

    subtitle = f"Complexity: {spec.complexity_text}"
    if scale != 1.0:
        subtitle = f"{subtitle} | scaled for readability"
    _draw_line_chart(
        x_values=n,
        series=scaled_series,
        title=spec.title,
        subtitle=subtitle,
        out_path=out_path,
    )
    return out_path


def iter_code_files(lab_dir: Path) -> Iterable[Path]:
    """
    Enumerate code files to graph inside a lab directory.
    We include .cpp/.c/.py and also "weird" filenames like "forward,cpp".
    """

    allowed_exts = {".py", ".cpp", ".c", ".h", ".hpp"}
    # Skip our own plotting utilities to avoid generating graphs-for-graphs.
    skip_names = {
        "generate_time_complexity_images.py",
        "time_complexity_plotter.py",
    }
    for p in lab_dir.rglob("*"):
        if not p.is_file():
            continue

        # Skip images (outputs), but allow code files under Graph/ if they exist.
        if any(part.lower() == "images" for part in p.parts):
            continue
        if p.name in skip_names:
            continue

        if p.suffix.lower() in allowed_exts:
            yield p
            continue

        # Handle cases like "forward,cpp" (no extension, but contains 'cpp').
        name_lower = p.name.lower()
        if "cpp" in name_lower:
            yield p


def generate_plots_for_lab(lab_dir: Path, *, output_dir: Path) -> list[Path]:
    """
    Generate time complexity graphs for every code file within `lab_dir` and save them in `output_dir`.

    For each file we generate ONLY:
      - an absolute/arbitrary-units plot (`time_complexity_absolute_*.png`)
    """

    generated: list[Path] = []
    for file_path in sorted(iter_code_files(lab_dir)):
        o_exprs = extract_time_complexity_o_expressions(file_path)
        spec = PlotSpec(
            file_path=file_path,
            o_expressions=o_exprs,
            title=extract_algorithm_title(file_path),
            complexity_text=extract_time_complexity_text(file_path),
        )
        out_abs = generate_time_complexity_plot(spec, output_dir=output_dir)
        generated.append(out_abs)
    return generated

