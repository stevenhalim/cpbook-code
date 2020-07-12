open Scanf
open Printf

let modu a m =
  (a mod m + m) mod m

let extEuclid a b =
  let rec go a b x xx y yy =
    if b = 0 then
      a, x, y
    else
      let q = a / b in
      go b (a mod b) xx (x - q * xx) yy (y - q * yy)
  in
  go a b 1 0 0 1

let modInverse b m =
  let d, x, y = extEuclid b m in
  if d <> 1 then -1
  else modu x m

let crt rs ms =
  let mt = List.fold_left ( * ) 1 ms in
  List.map2
    (fun r m ->
       let a = modu (r * modInverse (mt / m) m) m in
       modu (a * (mt / m)) mt
    )
    rs ms
  |> List.fold_left (fun x y -> modu (x + y) mt) 0

let main =
  try
    let caseNo = ref 0 in
    while true do
      let e, m = scanf "%d %d\n" (fun e m -> e, m) in
      let orbit = [365; 687] in
      let rs = [365 - e; 687 - m] in
      let ans = crt rs orbit in
      incr caseNo;
      printf "Case %d: %d\n" !caseNo ans;
    done
  with End_of_file ->
    ()
