open Printf
open Int64

let _sieve_size = ref 0
let bs = Array.make 10000010 true

let rec mark_sieve start step =
  if start < !_sieve_size
  then begin
    bs.(start) <- false;
    mark_sieve (start+step) step
  end

(* returns a list of primes *)
let sieve upperbound =
  _sieve_size := upperbound + 1;
  let rec helper i acc =
    if i > upperbound then acc
    else if bs.(i)
    then
      begin
        if mul (of_int i) (of_int i) < (of_int !_sieve_size) (* check for overflow *)
        then mark_sieve (i*i) (2*i);
        helper (i+2) (i :: acc)
      end
    else helper (i+2) acc
  in 
  List.rev (helper 3 [2])

(* n is Int64, p is int *)
let divisible n p = 
  rem n (of_int p) = zero

let isPrime n primes = 
  if n < (of_int !_sieve_size) then begin
    let x = to_int n in
    if x = 2 then true
    else if x mod 2 = 0 then false
    else bs.(x)
  end
  else List.for_all (fun p -> not (divisible n p)) primes

(* second part *)
let primeFactors n primes =
  let rec helper x acc primes_left =
    if x = one then acc
    else match primes_left with 
      | [] -> x :: acc
      | hd :: tl ->
        if compare x (mul (of_int hd) (of_int hd)) = -1 then x :: acc
        else if divisible x hd
        then
          helper (div x (of_int hd)) ((of_int hd) :: acc) primes_left
        else
          helper x acc tl
  in
  List.rev (helper n [] primes) 

(* third part *)
let numPF n primes =
  let rec helper x ans primes_left =
    if x = one then ans
    else match primes_left with
      | [] -> ans + 1
      | hd :: tl ->
        if compare x (mul (of_int hd) (of_int hd)) = -1 then ans + 1
        else if divisible x hd
        then
          helper (div x (of_int hd)) (ans+1) primes_left
        else
          helper x ans tl
  in
  helper n 0 primes

let numDiffPF n primes =
  let rec divide_fully x p =
    if divisible x p
    then
      divide_fully (div x (of_int p)) p
    else x
  in 
  let rec helper x ans primes_left =
    if x = one then ans
    else match primes_left with
      | [] -> ans + 1
      | hd :: tl ->
        if compare x (mul (of_int hd) (of_int hd)) = -1 then ans + 1
        else if divisible x hd
        then
          helper (divide_fully x hd) (ans+1) primes_left (* count this pf only once *)
        else
          helper x ans tl
  in
  helper n 0 primes

let sumPF n primes =
  List.fold_left (add) 0L (primeFactors n primes)

let numDiv n primes =
  let rec divide_fully p = function 
    | (pow, x) when divisible x p -> divide_fully p (pow+1, (div x (of_int p)))
    | _ as pair -> pair
  in 
  let rec helper x ans primes_left =
    if x = one then ans
    else match primes_left with
      | [] -> mul ans 2L
      | hd :: tl ->
        if compare x (mul (of_int hd) (of_int hd)) = -1 then mul ans 2L
        else if divisible x hd
        then
          let (pow, y) = divide_fully hd (0,x) in
          helper y (mul ans (of_int (pow+1))) primes_left (* count this pf only once *)
        else
          helper x ans tl
  in
  helper n 1L primes

let power n pow =
  of_float ((to_float n) ** (Float.of_int pow))

let get_factor n pow =
  div (sub (power n (pow+1)) one) (sub n one)

let sumDiv n primes =
  let rec divide_fully p = function 
    | (pow, x) when divisible x p -> divide_fully p (pow+1, (div x (of_int p)))
    | _ as pair -> pair
  in 
  let rec helper x ans primes_left =
    if x = one then ans
    else match primes_left with
      | [] -> mul ans (get_factor x 1)
      | hd :: tl ->
        if compare x (mul (of_int hd) (of_int hd)) = -1 then mul ans (get_factor x 1)
        else if divisible x hd
        then
          let (pow, y) = divide_fully hd (0,x) in
          helper y (mul ans (get_factor (of_int hd) pow)) primes_left (* count this pf only once *)
        else
          helper x ans tl
  in
  helper n 1L primes

let eulerPhi n primes = 
  let rec divide_fully x p =
    if divisible x p
    then
      divide_fully (div x (of_int p)) p
    else x
  in 
  let rec helper x ans primes_left =
    if x = one then ans
    else match primes_left with
      | [] -> (sub ans (div ans x))
      | hd :: tl ->
        if compare x (mul (of_int hd) (of_int hd)) = -1 then (sub ans (div ans x))
        else if divisible x hd
        then
          helper (divide_fully x hd) (sub ans (div ans (of_int hd))) primes_left (* count this pf only once *)
        else
          helper x ans tl
  in
  helper n n primes

let () = 
  let primes = sieve 10000000 in 
  let n = List.length primes in 
  printf "%d\n" (List.nth primes (n-1));
  let rec first_beyond i =
    if isPrime i primes then 
      printf "The next prime beyond the last prime generated is %Ld\n" i
    else
      first_beyond (add i one)
  in 
  first_beyond 10000001L;
  printf "%B\n" (isPrime (sub (shift_left 1L 31) one) primes); (* 2^31-1 = 2147483647, 10-digits prime *)
  printf "%B\n" (isPrime 136117223861L primes);        (* not a prime, 104729*1299709 *)

  (* second part: prime factors *)
  List.iter (printf "> %Ld\n") (primeFactors (sub (shift_left 1L 31) one) primes); (* slowest, 2^31-1 = 2147483647 is a prime *)
  printf "\n";
  List.iter (printf "> %Ld\n") (primeFactors 136117223861L primes); (* slow, 2 large factors 104729 * 1299709 *)
  printf "\n";
  List.iter (printf "> %Ld\n") (primeFactors 142391208960L primes); (* faster, 2^10 * 3^4 * 5 * 7^4 * 11 * 13 *)
  printf "\n";
  List.iter (printf "> %Ld\n") (primeFactors 99999820000081L primes); (* this is the limit: 9999991^2 *)
  printf "\n";
  List.iter (printf "> %Ld\n") (primeFactors 100000380000361L primes); (* error, beyond 9999991^2 *)
  printf "\n";

  (* third part: prime factors variants *)
  printf "numPF(%Ld) = %d\n" 50L (numPF 50L primes); (* 2^1 * 5^2 => 3 *)
  printf "numDiffPF(%Ld) = %d\n" 50L (numDiffPF 50L primes); (* 2^1 * 5^2 => 2 *)
  printf "sumPF(%Ld) = %Ld\n" 50L (sumPF 50L primes);  (* 2^1 * 5^2 => 2 + 5 + 5 = 12 *)
  printf "numDiv(%Ld) = %Ld\n" 50L (numDiv 50L primes); (* 1, 2, 5, 10, 25, 50, 6 divisors *)
  printf "sumDiv(%Ld) = %Ld\n" 50L (sumDiv 50L primes); (* 1 + 2 + 5 + 10 + 25 + 50 = 93 *)
  printf "eulerPhi(%Ld) = %Ld\n" 50L (eulerPhi 50L primes); (* 20 integers < 50 are relatively prime with 50 *)
  printf "\n";

  (* special cases when N is a prime number *)
  printf "numPF(%Ld) = %d\n" 7L (numPF 7L primes); (* 7^1 => 1 *)
  printf "numDiffPF(%Ld) = %d\n" 7L (numDiffPF 7L primes); (* 7^1 => 1 *)
  printf "sumPF(%Ld) = %Ld\n" 7L (sumPF 7L primes);  (* 7^1 => 7 *)
  printf "numDiv(%Ld) = %Ld\n" 7L (numDiv 7L primes); (* 1 and 7, 2 divisors *)
  printf "sumDiv(%Ld) = %Ld\n" 7L (sumDiv 7L primes); (* 1 + 7 = 8 *)
  printf "eulerPhi(%Ld) = %Ld\n" 7L (eulerPhi 7L primes) (* 6 integers < 7 are relatively prime with prime number 7 *)
