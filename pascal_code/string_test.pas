program stringtest;

type
    string5 = array [1..5] of char;
    string8 = array [1..8] of char;

var
    str5, strV : string5;
    str8 : string8;

procedure testStrings(var s5 : string5; s8 : string8);
    var
        b1, b2, b3 : boolean;

    begin
        b1 := s5 > s8;
        b2 := s5 < 'goodbye';
        b3 := 'nobody' >= s8;

        writeln(b1:6, b2:6, b3:6);
    end;

begin
    str5 := 'hello';
    str8 := 'everyone';
    writeln('''', str5, ', ', str8, '''');

    testStrings(str5, str8);

    str5 := str8; {truncate}
    strV := str5;
    writeln('''', str5, ', ', strV, ', ',str8, '''');

    str5 := 'hello';
    str8 := str5; {blank pad}
    writeln('''', str8, '''');
end.