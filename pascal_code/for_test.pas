program ForTest;

type
    grades = (A, B, C, D , F);

var
    i, j, k, n : integer;
    grade : grades;
    ch : char;

begin {For Statements}
    j := 2;
    ch := 'x';

    for k := j to 5 do
    begin
        n := k;
    end;

    for k := n+1 downto j+2 do i := k;

    for i := 1 to 2 do
    begin
        for j := 1 to 3 do
        begin
            k := i*j;
        end
    end;
    
    for grade := F downto A do i := ord(grade);

    for i := ord(ch) to ord('z') do j := i;
end.