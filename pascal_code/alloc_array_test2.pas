program AllocArrayTest2;

type
    string = array[1..5] of char;
    vector = array[0..9] of string;
    matrix = array[0..4, 0..3] of string;
    cube = array[0..1, 0..2, 0..3] of string;

var
    a1 : vector;
    a2 : matrix;
    a3 : cube;

begin
end.