(* note: for example usage of bitset, see ch5/primes.ml *)

open Printf

let isOn s j = s land 1 lsl j
let setBit s j = s lor 1 lsl j
let clearBit s j = s land lnot (1 lsl j)
let toggleBit s j = s lxor 1 lsl j
let lowBit s = s land -s
let setAll n = 1 lsl n - 1

let modulo s n = s land (n - 1) (* returns S % N, where N is a power of 2 *)
let isPowerOfTwo s = s land (s - 1) = 0
let nearestPowerOfTwo s = 1 lsl truncate (log (float s) /. log 2. +. 0.5)
let turnOffLastBit s = s land (s - 1)
let turnOnLastZero s = s lor (s + 1)
let turnOffLastConsecutiveBits s = s land (s + 1)
let turnOnLastConsecutiveZeroes s = s lor (s - 1)

let printSet vS =                             (* in binary representation *)
  printf "S = %2d = " vS;
  let rec aux vS =
    if vS > 0 then (
      aux (vS / 2);
      printf "%d" (vS mod 2)
    ) in
  aux vS;
  printf "\n"

let () =
  let s = ref 0 in
  let t = ref 0 in

  printf "1. Representation (all indexing are 0-based and counted from right)\n";
  s := 34; printSet !s;
  printf "\n";

  printf "2. Multiply S by 2, then divide S by 4 (2x2), then by 2\n";
  s := 34; printSet !s;
  s := !s lsl 1; printSet !s;
  s := !s lsr 2; printSet !s;
  s := !s lsr 1; printSet !s;
  printf "\n";

  printf "3. Set/turn on the 3-rd item of the set\n";
  s := 34; printSet !s;
  s := setBit !s 3; printSet !s;
  printf "\n";

  printf "4. Check if the 3-rd and then 2-nd item of the set is on?\n";
  s := 42; printSet !s;
  t := isOn !s 3; printf "T = %d, %s\n" !t (if !t <> 0 then "ON" else "OFF");
  t := isOn !s 2; printf "T = %d, %s\n" !t (if !t <> 0 then "ON" else "OFF");
  printf "\n";

  printf "5. Clear/turn off the 1-st item of the set\n";
  s := 42; printSet !s;
  s := clearBit !s 1; printSet !s;
  printf "\n";

  printf "6. Toggle the 2-nd item and then 3-rd item of the set\n";
  s := 40; printSet !s;
  s := toggleBit !s 2; printSet !s;
  s := toggleBit !s 3; printSet !s;
  printf "\n";

  printf "7. Check the first bit from right that is on\n";
  s := 40; printSet !s;
  t := lowBit !s; printf "T = %d (this is always a power of 2)\n" !t;
  s := 52; printSet !s;
  t := lowBit !s; printf "T = %d (this is always a power of 2)\n" !t;
  printf "\n";

  printf "8. Turn on all bits in a set of size n = 6\n";
  s := setAll 6; printSet !s;
  printf "\n";

  printf "9. Other tricks (not shown in the book)\n";
  printf "8 %% 4 = %d\n" (modulo 8 4);
  printf "7 %% 4 = %d\n" (modulo 7 4);
  printf "6 %% 4 = %d\n" (modulo 6 4);
  printf "5 %% 4 = %d\n" (modulo 5 4);
  printf "is %d power of two? %B\n" 9 (isPowerOfTwo 9);
  printf "is %d power of two? %B\n" 8 (isPowerOfTwo 8);
  printf "is %d power of two? %B\n" 7 (isPowerOfTwo 7);
  for i = 1 to 16 do
    printf "Nearest power of two of %d is %d\n" i (nearestPowerOfTwo i); (* special case for i == 0 *)
  done;
  printf "S = %d, turn off last bit in S, S = %d\n" 40 (turnOffLastBit 40);
  printf "S = %d, turn on last zero in S, S = %d\n" 41 (turnOnLastZero 41);
  printf "S = %d, turn off last consecutive bits in S, S = %d\n" 39 (turnOffLastConsecutiveBits 39);
  printf "S = %d, turn on last consecutive zeroes in S, S = %d\n" 36 (turnOnLastConsecutiveZeroes 36);
