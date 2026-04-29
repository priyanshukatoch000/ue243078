from __future__ import annotations

import sys
from pathlib import Path

LAB_DIR = Path(__file__).resolve().parents[1]
ROOT_DIR = LAB_DIR.parent  # ue243078/

sys.path.insert(0, str(ROOT_DIR))
from graph_utils.time_complexity_plotter import generate_plots_for_lab  # noqa: E402


def main() -> None:
    output_dir = LAB_DIR / "images"
    generated = generate_plots_for_lab(LAB_DIR, output_dir=output_dir)
    print(f"Generated {len(generated)} time-complexity images in: {output_dir}")


if __name__ == "__main__":
    main()

