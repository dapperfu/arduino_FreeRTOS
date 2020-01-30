
step_output.csv: a.out
	./a.out > step_output.csv

a.out:
	clang-9 low_pass_step.c low_pass.c

.PHONY: clean
clean:
	rm -rf a.out step_output.csv

StepResponseAnalysis.md: StepResponseAnalysis.ipynb step_output.csv
	jupyter-nbconvert --ExecutePreprocessor.timeout=600 --execute --to markdown --output=${@} ${<}
