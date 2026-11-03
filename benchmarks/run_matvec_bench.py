import csv
import math
import subprocess
from pathlib import Path

def main():
    
    root= Path(__file__).resolve().parent.parent
    executable = root / "build" / "Release" / "tinyinfer.exe"

    print(f"Executable:{executable}")

    if executable.exists():
        print(f"Exists:{executable.exists()}")
    else:
        raise FileNotFoundError("Executable not found")
    sizes = [128, 256, 512]

    

    results=[]
    header = ["rows", "cols", "time_ms"]

    for size in sizes:
        print(f"{size}x{size}")
        
        command = [str(executable), "matvec", "--rows", str(size), "--cols", str(size)]
        try:
            result=subprocess.run(command, capture_output=True, text= True, check= True)
            print(repr(result.stdout))
        except subprocess.CalledProcessError as error:
            print(f"Command failed: {command}")
            print(f"Exit code: {error.returncode}")
            print(f"Error output: {error.stderr}")
            raise

        lines=result.stdout.splitlines()
        time_ms=None
        for line in lines:
            line=line.strip()
            if line.startswith("Elapsed time:"):
                word=line.split()[2]
                try:
                    time_ms=float(word)
                except ValueError as error:
                    raise ValueError(
                        f"Invalid timing value '{word}' for {size}x{size}"
                    ) from error
                break

        if time_ms is None:
            raise ValueError("Elapsed time not found in program output")
        if not math.isfinite(time_ms) or time_ms < 0:
            raise ValueError(
                f"Invalid benchmark time for {size}x{size}: {time_ms}"
            )

        print(f"Time for {size}x{size} : {time_ms}")
        results.append([size,size,time_ms])

    directory_path=root/"benchmarks/results"
    directory_path.mkdir(parents=True, exist_ok=True)
    results_path= directory_path/"matvec_results.csv"
    with open(results_path, mode= 'w', newline='') as file:
        writer=csv.writer(file)
        writer.writerow(header)
        writer.writerows(results)


    print(f"Path of the benchmark: {results_path}")

        
    
    return
 

if __name__ == "__main__":
    main()