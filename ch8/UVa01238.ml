(* Free Parentheses *)

open Scanf
open Printf

let num = Array.make 35 0
let sign = Array.make 35 0
let cnt = ref 0
let memo = Hashtbl.create 100
let s = Hashtbl.create 100

let rec dp opens n value =
  if not (Hashtbl.mem memo (opens, n, value)) then begin
    if n = !cnt-1
    then begin
      Hashtbl.replace s value ()
    end
    else begin
      let nval = sign.(n+1) * num.(n+1) * (if opens mod 2 = 0 then 1 else -1) in
      let newval = value+nval and nx = n+1 in
      if opens > 0 then begin dp (opens-1) nx newval end;
      if sign.(nx) = -1 then dp (opens+1) nx newval;
      dp opens nx newval;
      Hashtbl.replace memo (opens, n, value) ()
    end
  end

let () =
  try
    while true do 
      let line = input_line stdin in
      let stream = Scanning.from_string line in
      Hashtbl.reset s;
      sign.(0) <- 1;
      cnt := 1;
      bscanf stream "%d" (fun x -> num.(0) <- x);
      try
        while true do
          bscanf stream " %c %d" (fun x y ->
            sign.(!cnt) <- if x = '-' then -1 else 1;
            num.(!cnt) <- y;
            incr cnt;
          )
        done
      with End_of_file ->
        ()
      ;
      Hashtbl.reset memo;
      dp 0 0 num.(0);
      printf "%d\n" (Hashtbl.length s)
    done
  with End_of_file ->
    ()

(* int main() {
  string s;
  char c;
  while (getline(cin, s)) {
    stringstream sin;
    sin << s;
    sin >> num[0];
    S.clear();
    sign[0] = 1;
    cnt = 1;
    while (sin >> c) {
      sign[cnt] = c == '-' ? -1 : 1;
      sin >> num[cnt];
      cnt++;
    }
    memset(memo, -1, sizeof memo);
    dp(0, 0, num[0]);
    printf("%d\n", (int)S.size());
  }
  return 0;
} *)
