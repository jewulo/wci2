program IfTest;

var
    i, j, t, f : integer;

begin {IF statments}
    i := 3; j := 4; t := 0; f := 0;

    if i < j then t := 300;

    if i = j then t := 200
             else f := -200;

    {Cascading IF THEN ELSEs.}
    if      i = 1 then f := 10
    else if i = 2 then f := 20
    else if i = 3 then f := 30
    else if i = 4 then f := 40
    else               f := -1;

    {The "dangling ELSE".}
    if i = j then if j = 2 then t := 500 else f := -500;
end.
