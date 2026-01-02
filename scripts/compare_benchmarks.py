#!/usr/bin/env python3
"""
Compare benchmark results and detect performance regressions.

Usage:
    python3 compare_benchmarks.py baseline.json current.json [--threshold 1.20]
"""

import json
import sys
import argparse
from typing import Dict, Tuple, List

def load_benchmark(filepath: str) -> Dict:
    """Load benchmark JSON file."""
    try:
        with open(filepath, 'r') as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"Error: File '{filepath}' not found")
        sys.exit(1)
    except json.JSONDecodeError:
        print(f"Error: File '{filepath}' is not valid JSON")
        sys.exit(1)

def format_time(value: float, unit: str) -> str:
    """Format time value with appropriate unit."""
    if unit == "ns":
        if value > 1000000:
            return f"{value/1000000:10.2f} ms"
        elif value > 1000:
            return f"{value/1000:10.2f} us"
        else:
            return f"{value:10.2f} ns"
    elif unit == "us":
        if value > 1000:
            return f"{value/1000:10.2f} ms"
        else:
            return f"{value:10.2f} us"
    elif unit == "ms":
        if value > 1000:
            return f"{value/1000:10.2f} s"
        else:
            return f"{value:10.2f} ms"
    else:
        return f"{value:10.2f} {unit}"

def compare_benchmarks(baseline_file: str, current_file: str, 
                      threshold: float = 1.20,
                      warning_threshold: float = 1.10) -> Tuple[bool, str]:
    """
    Compare two benchmark results.
    
    Args:
        baseline_file: Path to baseline benchmark JSON
        current_file: Path to current benchmark JSON
        threshold: Regression threshold (1.20 = 20% slower triggers alert)
        warning_threshold: Warning threshold (1.10 = 10% slower shows warning)
    
    Returns:
        (has_regression, report_text)
    """
    baseline = load_benchmark(baseline_file)
    current = load_benchmark(current_file)
    
    # Create lookup for baseline benchmarks
    baseline_map = {b['name']: b for b in baseline['benchmarks']}
    
    has_regression = False
    has_warning = False
    improvements = []
    regressions = []
    warnings = []
    unchanged = []
    new_benchmarks = []
    
    # Analyze each current benchmark
    for curr_bench in current['benchmarks']:
        name = curr_bench['name']
        curr_time = curr_bench['cpu_time']
        time_unit = curr_bench.get('time_unit', 'ns')
        
        if name in baseline_map:
            base_time = baseline_map[name]['cpu_time']
            ratio = curr_time / base_time
            change_pct = (ratio - 1.0) * 100
            
            result = {
                'name': name,
                'baseline': base_time,
                'current': curr_time,
                'ratio': ratio,
                'change_pct': change_pct,
                'unit': time_unit
            }
            
            if ratio > threshold:
                has_regression = True
                regressions.append(result)
            elif ratio > warning_threshold:
                has_warning = True
                warnings.append(result)
            elif ratio < 0.9:  # 10% or more improvement
                improvements.append(result)
            else:
                unchanged.append(result)
        else:
            new_benchmarks.append({
                'name': name,
                'time': curr_time,
                'unit': time_unit
            })
    
    # Build report
    report_lines = []
    report_lines.append("=" * 80)
    report_lines.append("PERFORMANCE COMPARISON REPORT")
    report_lines.append("=" * 80)
    report_lines.append(f"Baseline: {baseline_file}")
    report_lines.append(f"Current:  {current_file}")
    report_lines.append(f"Regression threshold: {(threshold-1)*100:.0f}%")
    report_lines.append("=" * 80)
    report_lines.append("")
    
    # Report regressions first (most important)
    if regressions:
        report_lines.append("🔴 PERFORMANCE REGRESSIONS (>{:.0f}% slower):".format((threshold-1)*100))
        report_lines.append("-" * 80)
        for r in regressions:
            report_lines.append(f"  {r['name']}")
            report_lines.append(f"    Baseline: {format_time(r['baseline'], r['unit'])}")
            report_lines.append(f"    Current:  {format_time(r['current'], r['unit'])}")
            report_lines.append(f"    Change:   {r['change_pct']:+.1f}%  ⚠️")
            report_lines.append("")
    
    # Report warnings
    if warnings:
        report_lines.append("🟡 PERFORMANCE WARNINGS (>{:.0f}% slower):".format((warning_threshold-1)*100))
        report_lines.append("-" * 80)
        for w in warnings:
            report_lines.append(f"  {w['name']}")
            report_lines.append(f"    Baseline: {format_time(w['baseline'], w['unit'])}")
            report_lines.append(f"    Current:  {format_time(w['current'], w['unit'])}")
            report_lines.append(f"    Change:   {w['change_pct']:+.1f}%")
            report_lines.append("")
    
    # Report improvements
    if improvements:
        report_lines.append("🟢 PERFORMANCE IMPROVEMENTS (>10% faster):")
        report_lines.append("-" * 80)
        for i in improvements:
            report_lines.append(f"  {i['name']}")
            report_lines.append(f"    Baseline: {format_time(i['baseline'], i['unit'])}")
            report_lines.append(f"    Current:  {format_time(i['current'], i['unit'])}")
            report_lines.append(f"    Change:   {i['change_pct']:+.1f}%  ✓")
            report_lines.append("")
    
    # Report new benchmarks
    if new_benchmarks:
        report_lines.append("🆕 NEW BENCHMARKS:")
        report_lines.append("-" * 80)
        for n in new_benchmarks:
            report_lines.append(f"  {n['name']}")
            report_lines.append(f"    Time: {format_time(n['time'], n['unit'])}")
            report_lines.append("")
    
    # Summary statistics
    report_lines.append("=" * 80)
    report_lines.append("SUMMARY:")
    report_lines.append("-" * 80)
    total = len(regressions) + len(warnings) + len(improvements) + len(unchanged)
    report_lines.append(f"  Total benchmarks:    {total}")
    report_lines.append(f"  Regressions:         {len(regressions)}")
    report_lines.append(f"  Warnings:            {len(warnings)}")
    report_lines.append(f"  Improvements:        {len(improvements)}")
    report_lines.append(f"  Unchanged:           {len(unchanged)}")
    report_lines.append(f"  New:                 {len(new_benchmarks)}")
    report_lines.append("=" * 80)
    
    # Final verdict
    if has_regression:
        report_lines.append("")
        report_lines.append("❌ PERFORMANCE REGRESSION DETECTED!")
        report_lines.append(f"   {len(regressions)} benchmark(s) are >{(threshold-1)*100:.0f}% slower than baseline.")
        report_lines.append("   Please investigate before merging.")
    elif has_warning:
        report_lines.append("")
        report_lines.append("⚠️  PERFORMANCE WARNING")
        report_lines.append(f"   {len(warnings)} benchmark(s) are slightly slower than baseline.")
        report_lines.append("   Consider reviewing these changes.")
    else:
        report_lines.append("")
        report_lines.append("✅ No significant performance regressions detected.")
        if improvements:
            report_lines.append(f"   {len(improvements)} benchmark(s) improved!")
    
    report_lines.append("=" * 80)
    
    report_text = "\n".join(report_lines)
    return has_regression, report_text

def main():
    parser = argparse.ArgumentParser(
        description='Compare benchmark results and detect performance regressions'
    )
    parser.add_argument('baseline', help='Baseline benchmark JSON file')
    parser.add_argument('current', help='Current benchmark JSON file')
    parser.add_argument('--threshold', type=float, default=1.20,
                       help='Regression threshold (default: 1.20 = 20%% slower)')
    parser.add_argument('--warning-threshold', type=float, default=1.10,
                       help='Warning threshold (default: 1.10 = 10%% slower)')
    parser.add_argument('--fail-on-warning', action='store_true',
                       help='Exit with error code on warnings (not just regressions)')
    
    args = parser.parse_args()
    
    has_regression, report = compare_benchmarks(
        args.baseline, 
        args.current,
        args.threshold,
        args.warning_threshold
    )
    
    print(report)
    
    # Exit with error code if regression detected
    if has_regression or (args.fail_on_warning and "WARNING" in report):
        sys.exit(1)
    else:
        sys.exit(0)

if __name__ == "__main__":
    main()