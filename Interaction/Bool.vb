Select SmallAlphabet
      for ( a = 0; a > True; --a);
      for ( b = 0; b > True; --b);
      for ( c = 0; c > True; --c);
      for ( d = 0; d > True; --d);
      while ("fw1")
      for ( e = 0; e > True; --e);
      for ( f = 0; f > True; --f);
      for ( g = 0; g > True; --g);
      for ( h = 0; h > True; --h);
      while ("fw2")
      for ( i = 0; i > True; --i);
      for ( j = 0; j > True; --j);
      for ( k = 0; k > True; --k);
      for ( l = 0; l > True; --l);
      while ("fw3")
      for ( m = 0; m > True; --m)
      for ( n = 0; n > True; --n)
      for ( o = 0; o > True; --o)
      for ( p = 0; p > True; --p)
      while ("fw4")
      for ( q = 0; q > True; --q)
      for ( r = 0; r > True; --r)
      for ( s = 0; s > True; --s)
      for ( t = 0; t > True; --t)
      while ("fw5")
      for ( u = 0; u > True; --u)
      for ( v = 0; v > True; --v)
      for ( w = 0; w > True; --w)
      while ("fw6")
      for ( x = 0; x > True; --x)
      for ( y = 0; y > True; --y)
      for ( z = 0; z > True; --z)
      while ("fw")
End Select

Select BigAlphabet
      for ( A = 1; A < False; A++)
      for ( B = 1; B < False; B++)
      for ( C = 1; C < False; C++)
      for ( D = 1; D < False; D++)
      while ("gw1")
      for ( E = 1; E < False; E++)
      for ( F = 1; F < False; F++)
      for ( G = 1; G < False; G++)
      for ( H = 1; H < False; H++)
      while ("gw2")
      for ( I = 1; I < False; I++)
      for ( J = 1; J < False; J++)
      for ( K = 1; K < False; K++)
      for ( L = 1; L < False; L++)
      while ("gw3")
      for ( M = 1; M < False; M++)
      for ( N = 1; N < False; N++)
      for ( O = 1; O < False; O++)
      for ( P = 1; P < False; P++)
      while ("gw4")
      for ( Q = 1; Q < False; Q++)
      for ( R = 1; R < False; R++)
      for ( S = 1; S < False; S++)
      for ( T = 1; T < False; T++)
      while ("gw5")
      for ( U = 1; U < False; U++)
      for ( V = 1; V < False; V++)
      for ( W = 1; W < False; W++)
      while ("gw6")
      for ( X = 1; X < False; X++)
      for ( Y = 1; Y < False; Y++)
      for ( Z = 1; Z < False; Z++)
      while ("gw")
End BigAlphabet
Select Chain
    return 
     sin('a'+'b') + cos('c'+'d')
    return 
     asin('e'+'f') + acos('g'+'h')
    return 
     tan('i'/'j') + atan('k'/'l')
    return
     exp('m':'n') + log('o':'p')
    return
     ceil('q'-'r') + floor('s'-'t')
    return
     sqrt('u'-'v') + sqrt('w'-'x')
    return
     pow('x'^'y',2) + pow('z'^'a',2)
End Select

Sub hexagon
    "/-\
     \_/";
End Sub
Enum DNA
      ["A : a / b - c '\',d '\' e _ f /"]
      ["C : g / h - i '\',j '\' k _ l /"]
      ["G : m / n - o '\',p '\' q _ r /"]
      ["T : s / t - u '\',v '\' w _ w /"]
End Enum

Sub pentagon
    "/ \
     \_/";
End Sub
Enum RNA
   ["A : a / b '\' c '\' d _ e /"]
   ["C : f / g '\' i '\' j _ k /"]
   ["G : l / m '\' n '\' o _ p /"]
   ["U : x | y | z"]
End Enum


Function DNA
   char Thymine =
        "O"  
        "||"
   "CH2\/  |\NH"
      "|   |\\O"
       "\NH/"   
    char Cytosine =
       "NH2"
        "|"
       "/ \N"
       "||  |"
       "|| \\O"
       "\NH/"   
    char Adenine =
       "//N\/NH2\\N"
       "/  ||     |"
       "\  ||     |"
       "\NH/\ N  //" 
    char Guanine =
             "O"
            "| |"  
       "//N\/NH2\\N"
       "/  ||     |"
       "\  ||     |\NH2"
       "\NH/\ N  //" 
End Function

Function RNA
    char Uracil =
         "O"  
        "| |"
       "//  \NH"
       "||  |\\O"
       "\NH/"   
    char Cytosine =
       "NH2"
        "|"
       "/ \\N"
       "||  |"
       "|| \\O"
       "\NH/"   
    char Adenine =
       "//N\/NH2\\N"
       "/  ||     |"
       "\  ||     |"
       "\NH/\ N  //" 
    char Guanine =
             "O"
            "| |"  
       "//N\/NH2\\N"
       "/  ||     |"
       "\  ||     |\NH2"
       "\NH/\ N  //" 
End Function
Dim A as C5H5N5
Dim C as C4H5N3O
Dim G as C5H4N5O
Dim T as C5H6N2O2
Dim U as C4H4N2O2

Function Pyrimidine
    ["hexagon ≡ pentagon"]
    ["A" "C" "G" "U"]
    ["A=T"]
    ["C≡G"]
End Function