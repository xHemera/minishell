#!/bin/sh

MINISHELL_EXEC=./minishell
OUT_DIR=tester
TMP_OUT=$OUT_DIR/minishell_output.txt
TMP_EXP=$OUT_DIR/expected_output.txt

mkdir -p "$OUT_DIR"

i=1

run_test() {
	cmd="$1"
	printf "Test %02d: %s\n" "$i" "$cmd"
	echo "$cmd" | $MINISHELL_EXEC > "$TMP_OUT" 2>&1
	echo "$cmd" | bash > "$TMP_EXP" 2>&1
	if diff -q "$TMP_OUT" "$TMP_EXP" > /dev/null; then
		echo "✅ OK"
	else
		echo "❌ FAIL"
		diff "$TMP_OUT" "$TMP_EXP"
	fi
	i=$((i + 1))
}

run_test "echo test builtin echo"
run_test "pwd"
run_test "cd / && pwd"
run_test "cd invalid_dir"
run_test "echo erreur cd doit etre detectee"
run_test "export TEST_VAR=42 && echo \$TEST_VAR"
run_test "unset TEST_VAR && echo \$TEST_VAR"
run_test "ls -l | grep minishell"
run_test "echo test > $OUT_DIR/tmp_test_file"
run_test "cat < $OUT_DIR/tmp_test_file"
run_test "echo test >> $OUT_DIR/tmp_test_file"
run_test "cat $OUT_DIR/tmp_test_file"
run_test "rm $OUT_DIR/tmp_test_file"
run_test "command_inexistant"

$MINISHELL_EXEC -c "exit 42" > /dev/null 2>&1
echo "Test final: exit status"
if [ $? -eq 42 ]; then
	echo "✅ Exit code OK"
else
	echo "❌ Exit code FAIL"
fi

rm -f "$TMP_OUT" "$TMP_EXP"
