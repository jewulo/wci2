program newton1 (input, output);

const
    epsilon = 1e-6;

type
    positive = 0..32767;

var
    number : positive;
    
function root(x : real) : real;
    var
        r : real;
    
    begin
        r := 1;

        r := (x/r + r)/2;
        r := (x/r + r)/2;
        r := (x/r + r)/2;
        r := (x/r + r)/2;
        r := (x/r + r)/2;
        r := (x/r + r)/2;
        r := (x/r + r)/2;
        r := (x/r + r)/2;

        root := r;
    end

procedure print(n : integer; root : real);
    begin
    writeln('The square of ', n:4, ' is ', root:8:4);
    end;

begin
    writeln;
    write('Enter a new number: ');
    read(number);
    print(number, root(number));

    writeln;
    write('Enter a new number: ');
    read(number);
    print(number, root(number));
end.
