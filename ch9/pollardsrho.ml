open Printf

let mulmod a b c =
  let rec go x y acc =
    if y = 0 then acc
    else go (x * 2 mod c) (y / 2) ((acc + (y mod 2) * x) mod c)
  in go a b 0

let rec gcd a b = if b = 0 then a else gcd b (a mod b)

let pollard_rho n =
  let rec go x y =
    let d = gcd (abs (y - x)) n in
    if d != 1 && d != n then d
    else go (tortoise x) (hare y)
  and tortoise x = (mulmod x x n + n - 1) mod n
  and hare x = tortoise (tortoise x) in
  go (tortoise 3) (hare 3)

let () =
  let n = 2063512844981574047 in
  let ans = pollard_rho n in
  let ans = min ans (n / ans) in
  printf "%d %d\n" ans (n / ans)
