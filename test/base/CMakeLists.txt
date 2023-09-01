macro (add_base_test_exec exec_name)
    add_executable ("${exec_name}" "${exec_name}.cpp")
    target_link_libraries ("${exec_name}" qserver_base  ${ARGN})
endmacro (add_base_test_exec)