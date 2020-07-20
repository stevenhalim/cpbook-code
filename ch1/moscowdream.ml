open Scanf
open Printf

let () =
  scanf "%d %d %d %d\n" (fun a b c n ->
    if (a >= 1) && (b >= 1) && (c >= 1) && (a+b+c >= n) && (n >= 3) then
      printf "YES\n"
    else
      printf "NO\n"
  )
