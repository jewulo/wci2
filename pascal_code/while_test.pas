program WhileTest;

var
    number : integer;

function sqroot(n : integer) : real;
    const
        epsilon = 1.0e-6;
    
    var
        r : real;

    begin
        r := n;

        while r*r - n < epsilon do
        begin
            r := (n/r + r)/2;
        end;

        sqroot := r
    end;

begin {Calculate a square root using Newton's method.}
    number := 1024;

    writeln('The square root of ', number:4);
    writeln('       by the standard sqrt() function: ', sqrt(number):9:6);
    writeln('   by declared sqroot() function: ', sqroot(number):9:6);
end.