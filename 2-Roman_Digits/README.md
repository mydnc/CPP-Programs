The task is to develop a program to solve arithmetic puzzles with roman numbers.

Assume a sequence of characters - the roman digits I, V, X, L, C, D, and M. The puzzle is to place + signs into the sequence such that the result is a string that consists of valid roman numbers and the sum of the roman numbers equals to some given value n. For example, input IVIIIVI and n=13 may result into the following valid expressions:

    13 = I+V+I+I+IV+I
    13 = I+V+II+IV+I
    13 = I+VI+I+IV+I
    13 = I+VII+IV+I
    13 = IV+I+I+I+V+I
    13 = IV+I+I+I+VI
    13 = IV+I+II+V+I
    13 = IV+I+II+VI
    13 = IV+II+I+V+I
    13 = IV+II+I+VI
    13 = IV+III+V+I
    13 = IV+III+VI

The program must be able to find all possible solutions of the puzzle and count the number of such solutions.

The first line of the input is a sequence of uppercase letters. The letters are not separated by any whitespace. This is the puzzle to solve, the program is about to place the + operators somewhere into this sequence. Following the first line, there is a list of commands. The commands are of two kinds:

    -count n computes the number of solutions for the puzzle (i.e., how may options there exist such that the sum is equal to n,
    -list n is similar to the previous command, moreover, the program shall print out all solutions.

The output of the program is either the number of solutions (command count n) or the list of solutions and their count (command list n). The exact output format is shown in the examples below.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:

    -there are invalid characters in the input sequence (only I, V, X, L, C, D, and M is valid),
    -the command is neither list n nor count n,
    -the number n is invalid, not an integer, negative, or zero.

Sample program runs:
-----------------------------------------------------------------------------------
    Sequence:
    IIIVIII
    Operations:
    list 9
    > 9 = I+I+IV+I+I+I
    > 9 = I+I+IV+I+II
    > 9 = I+I+IV+II+I
    > 9 = I+I+IV+III
    > 9 = II+IV+I+I+I
    > 9 = II+IV+I+II
    > 9 = II+IV+II+I
    > 9 = II+IV+III
    9: 8
    count 11
    11: 32
    list 10
    10: 0
    count 10
    10: 0
-----------------------------------------------------------------------------------
    Sequence:
    IIXIIVIIXXLXXCXX
    Operations:
    list 225
    > 225 = I+IX+I+IV+I+IX+X+L+X+X+C+X+X
    > 225 = I+IX+I+IV+I+IX+X+L+X+X+C+XX
    > 225 = I+IX+I+IV+I+IX+X+L+X+X+CX+X
    > 225 = I+IX+I+IV+I+IX+X+L+X+X+CXX
    > 225 = I+IX+I+IV+I+IX+X+L+XX+C+X+X
    > 225 = I+IX+I+IV+I+IX+X+L+XX+C+XX
    > 225 = I+IX+I+IV+I+IX+X+L+XX+CX+X
    > 225 = I+IX+I+IV+I+IX+X+L+XX+CXX
    > 225 = I+IX+I+IV+I+IX+X+LX+X+C+X+X
    > 225 = I+IX+I+IV+I+IX+X+LX+X+C+XX
    > 225 = I+IX+I+IV+I+IX+X+LX+X+CX+X
    > 225 = I+IX+I+IV+I+IX+X+LX+X+CXX
    > 225 = I+IX+I+IV+I+IX+X+LXX+C+X+X
    > 225 = I+IX+I+IV+I+IX+X+LXX+C+XX
    > 225 = I+IX+I+IV+I+IX+X+LXX+CX+X
    > 225 = I+IX+I+IV+I+IX+X+LXX+CXX
    225: 16
    list 205
    > 205 = I+IX+I+IV+I+IX+X+L+X+XC+X+X
    > 205 = I+IX+I+IV+I+IX+X+L+X+XC+XX
    > 205 = I+IX+I+IV+I+IX+X+LX+XC+X+X
    > 205 = I+IX+I+IV+I+IX+X+LX+XC+XX
    > 205 = I+IX+I+IV+I+IX+XL+X+X+C+X+X
    > 205 = I+IX+I+IV+I+IX+XL+X+X+C+XX
    > 205 = I+IX+I+IV+I+IX+XL+X+X+CX+X
    > 205 = I+IX+I+IV+I+IX+XL+X+X+CXX
    > 205 = I+IX+I+IV+I+IX+XL+XX+C+X+X
    > 205 = I+IX+I+IV+I+IX+XL+XX+C+XX
    > 205 = I+IX+I+IV+I+IX+XL+XX+CX+X
    > 205 = I+IX+I+IV+I+IX+XL+XX+CXX
    205: 12
    count 209
    209: 448
    count 229
    229: 768
    count 213
    213: 0
    list 195
    195: 0
-----------------------------------------------------------------------------------
    Sequence:
    IIIIIIIIIIIII
    Operations:
    count 13
    13: 1705
    count 11
    11: 0
-----------------------------------------------------------------------------------
    Sequence:
    MDCLXVIVXLCDM
    Operations:
    list 3309
    > 3309 = M+D+C+L+X+V+IV+XL+C+D+M
    > 3309 = M+D+C+L+XV+IV+XL+C+D+M
    > 3309 = M+D+C+LX+V+IV+XL+C+D+M
    > 3309 = M+D+C+LXV+IV+XL+C+D+M
    > 3309 = M+D+CL+X+V+IV+XL+C+D+M
    > 3309 = M+D+CL+XV+IV+XL+C+D+M
    > 3309 = M+D+CLX+V+IV+XL+C+D+M
    > 3309 = M+D+CLXV+IV+XL+C+D+M
    > 3309 = M+DC+L+X+V+IV+XL+C+D+M
    > 3309 = M+DC+L+XV+IV+XL+C+D+M
    > 3309 = M+DC+LX+V+IV+XL+C+D+M
    > 3309 = M+DC+LXV+IV+XL+C+D+M
    > 3309 = M+DCL+X+V+IV+XL+C+D+M
    > 3309 = M+DCL+XV+IV+XL+C+D+M
    > 3309 = M+DCLX+V+IV+XL+C+D+M
    > 3309 = M+DCLXV+IV+XL+C+D+M
    > 3309 = MD+C+L+X+V+IV+XL+C+D+M
    > 3309 = MD+C+L+XV+IV+XL+C+D+M
    > 3309 = MD+C+LX+V+IV+XL+C+D+M
    > 3309 = MD+C+LXV+IV+XL+C+D+M
    > 3309 = MD+CL+X+V+IV+XL+C+D+M
    > 3309 = MD+CL+XV+IV+XL+C+D+M
    > 3309 = MD+CLX+V+IV+XL+C+D+M
    > 3309 = MD+CLXV+IV+XL+C+D+M
    > 3309 = MDC+L+X+V+IV+XL+C+D+M
    > 3309 = MDC+L+XV+IV+XL+C+D+M
    > 3309 = MDC+LX+V+IV+XL+C+D+M
    > 3309 = MDC+LXV+IV+XL+C+D+M
    > 3309 = MDCL+X+V+IV+XL+C+D+M
    > 3309 = MDCL+XV+IV+XL+C+D+M
    > 3309 = MDCLX+V+IV+XL+C+D+M
    > 3309 = MDCLXV+IV+XL+C+D+M
    3309: 32
    count 3331
    3331: 64
-----------------------------------------------------------------------------------
    Sequence:
    MDCF
    Invalid input.
-----------------------------------------------------------------------------------
    Sequence:
    MCDXLIVCMXCIX
    Operations:
    count 2865
    2865: 128
    test 2643
    Invalid input.
-----------------------------------------------------------------------------------