import csv
from matplotlib import pyplot as plt
from pathlib import Path

def main():
    root= Path(__file__).resolve().parent.parent
    result_csv= root / "benchmarks"/ "results" / "matvec_results.csv"
    print(result_csv)
    if result_csv.exists():
        print(f"Result CSV found: {result_csv}")
    else:
        raise FileNotFoundError("Result CSV not found")
    matrix_sizes=[]
    execution_times=[]
    with open(result_csv, "r", newline="") as file:
        reader=csv.DictReader(file)
        
        for row in reader:
            rows=int(row["rows"])
            cols=int(row["cols"])
            time=float(row["time_ms"])
            matrix_sizes.append(rows)
            execution_times.append(time)

            print(f"Rows: {rows}, Cols: {cols}, Time: {time} ms")

    if not matrix_sizes:
        raise ValueError("No data found in the CSV file")
    print(matrix_sizes)   
    print(execution_times)   


    plt.figure(figsize=(10,6))
    plt.plot(matrix_sizes, execution_times, marker="x")
    plt.xlabel("Matrix dimension (N x N)")
    plt.ylabel("Execution Time (ms)")
    plt.title("Tiny Infer - MatVec Runtime")
    plt.grid(True)
    charts_dir = root / "benchmarks" / "charts"
    charts_dir.mkdir(parents=True, exist_ok=True)
    output_path = charts_dir / "matvec_runtime.png"
    plt.savefig(output_path)
    print(f"Chart saved to: {output_path}")
    plt.show()


if __name__ == "__main__":
    main()