program parmstest;

var
i, j : integer;
x, y : real;

procedure proc(ii : integer; var jj : integer; xx : real; var yy : real);
    begin
        ii := jj;
        yy := xx;
    end;

begin
    proc(i, j, x, y)
end.