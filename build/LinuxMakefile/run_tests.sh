# No Bugs in Production (NBP)
# Copyright (C) 2019-present Alin Enachescu

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

status=0
sanopt=""

function run_test {
    echo "running test $1"

    sample=${1%_sample}
    has_output=0
    expected_output=""
    output=""

    # load expected test output
    cd ../samples/$sample
    expected_printer_output=$(<expected_linux_printer_output.txt)
    if [ -f "expected_output.txt" ]; then
        has_output=1
        expected_output=$(<expected_output.txt)
    fi
    cd ../../bin

    # run and get test output
    cd $1
    if [ -f "output.txt" ]; then
        rm output.txt
    fi
    printer_output=""
    if [ -z "$sanopt" ]; then
        printer_output=$(./$1)
    else
        printer_output=$(env $sanopt ./$1)
    fi
    testStatus=$?

    if [ -f "output.txt" ]; then
        output=$(<output.txt)
    fi
    cd ..

    # check test return code
    if [ $testStatus -ne $2 ]; then
        echo "***** expected status: $2"
        echo "***** current status: $testStatus"
        echo $'test failed\n'
        status=1
        return
    fi

    # check printer output
    if [ "$expected_printer_output" != "$printer_output" ]; then
        echo "***** expected printer output *****"
        echo "$expected_printer_output"
        echo "***** printer output *****"
        echo "$printer_output"
        echo $'test failed\n'
        status=1
        return
    fi

    # check output file
    if [ $has_output -eq 1 ]; then
        if [ "$expected_output" != "$output" ]; then
            echo "***** expected output file *****"
            echo "$expected_output"
            echo "***** output file *****"
            echo "$output"
            echo $'test failed\n'
            status=1
            return
        fi
    fi

    echo $'test passed\n'
}

if test "$#" -eq 1; then
    sanopt=$1
    echo "$sanopt"
fi

cd ../../bin

run_test basic_sample 0
run_test modules_sample 0
run_test modules_one_file_sample 0
run_test submodules_sample 0
run_test submodules_one_file_sample 0
run_test main_module_fixtures_sample 0
run_test main_module_fixtures_one_file_sample 0
run_test main_module_setup_sample 0
run_test main_module_setup_one_file_sample 0
run_test main_module_teardown_sample 0
run_test main_module_teardown_one_file_sample 0
run_test module_fixtures_sample 0
run_test module_fixtures_one_file_sample 0
run_test test_fixtures_sample 0
run_test test_fixtures_one_file_sample 0
run_test check_sample 1
run_test test_and_module_sample 0
run_test test_and_module_fixtures_sample 0
run_test test_and_module_name_sample 0
run_test check_type_sample 0
run_test check_operator_sample 0
run_test assert_type_sample 0
run_test test_assert_type_sample 0
run_test module_assert_type_sample 0
run_test assert_operator_sample 0
run_test test_assert_operator_sample 0
run_test module_assert_operator_sample 0
run_test test_assert_sample 1
run_test module_assert_sample 1
run_test assert_sample 1

cd ../build/LinuxMakefile

exit $status