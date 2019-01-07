open Printf

let mulmod a b m =
  let rec go x y acc =
    if y = 0 then acc
    else go (x * 2 mod m) (y / 2) ((acc + (y mod 2) * x) mod m)
  in go a b 0

let rec gcd a b = if b = 0 then a else gcd b (a mod b)

let powmod a b m =
  let rec go x y acc =
    if y = 0 then acc
    else go (mulmod x x m) (y / 2) (if y mod 2 = 0 then acc else mulmod acc x m)
  in go a b 1

let witness x a =
  if x mod a = 0 then true
  else
    let n = x - 1 in
    let rec loop c d =
      if d = n then c <> 1
      else
        let c' = mulmod c c x in
        if c <> 1 && c <> x - 1 && c' = 1 then true
        else loop c' (d * 2) in
    let d = (n / (n land (- n))) in
    loop (powmod a d x) d

let is_prime n =
  (* Verified for all 64-bit integers *)
  let ws = [2; 3; 5; 7; 11; 13; 17; 19; 23; 29; 31; 37] in
  if List.mem n ws then true
  else if n < 40 then false
  else not (List.exists (witness n) ws)

let rec find_factor n =
  if n mod 2 = 0 then 2 else
  let start = Random.int (min (n - 2) (1 lsl 29)) + 2 in
  let c = Random.int 32 + 1 in
  let tortoise x = (mulmod x x n + c) mod n in
  let hare x = tortoise (tortoise x) in
  let rec go x y =
    let d = gcd (abs (y - x)) n in
    if d <> 1 then d
    else go (tortoise x) (hare y) in
  let d = go (tortoise start) (hare start) in
  if d <> n then d
  else find_factor n


let rec factorize n =
  if n = 1 then []
  else if is_prime n then [n]
  else let d = find_factor n in factorize d @ factorize (n / d)

let () =
  let () = assert (List.init 100000 (fun x -> x)
                    |> List.filter is_prime
                    |> List.length = 9592) in
  let n = 2063512844981574047 in
  let factors = factorize n in
  List.iter (printf "%d ") factors;
  print_newline ()
