open Printf

let swap a i j =
  let temp = a.(i) in a.(i) <- a.(j); a.(j) <- temp

let partition a l r =
  let p = a.(l) in                               (* p is the pivot *)
  let m = ref l in                               (* S1 and S2 are empty *)
  for k = l + 1 to r do                          (* explore unknown region *)
    if a.(k) < p then (                          (* case 2 *)
      m := !m + 1;
      swap a k !m
    ) (* notice that we do nothing in case 1: a[k] >= p *)
  done;
  swap a l !m;                                   (* swap pivot with a[m] *)
  !m                                             (* return pivot index *)

let randPartition a l r =
  let p = l + Random.int (r - l + 1) in          (* select a random pivot *)
  swap a l p;                                    (* swap A[p] with A[l] *)
  partition a l r

let rec quickSelect a l r k =                    (* expected O(n) *)
  if l = r then a.(l)
  else (
    let q = randPartition a l r in               (* O(n) *)
    if q + 1 = k then
      a.(q)
    else if q + 1 > k then
      quickSelect a l (q - 1) k
    else
      quickSelect a (q + 1) r k
  )

let () =
  let a = [|2; 8; 7; 1; 5; 4; 6; 3|] in          (* permutation of [1..8] *)
  printf "%d\n" (quickSelect a 0 7 8);           (* the output must be 8 *)
  printf "%d\n" (quickSelect a 0 7 7);           (* the output must be 7 *)
  printf "%d\n" (quickSelect a 0 7 6);           (* the output must be 6 *)
  printf "%d\n" (quickSelect a 0 7 5);           (* the output must be 5 *)
  printf "%d\n" (quickSelect a 0 7 4);           (* the output must be 4 *)
  printf "%d\n" (quickSelect a 0 7 3);           (* the output must be 3 *)
  printf "%d\n" (quickSelect a 0 7 2);           (* the output must be 2 *)
  printf "%d\n" (quickSelect a 0 7 1);           (* the output must be 1 *)

  (* try experimenting with the content of array A to see the behavior of "QuickSelect" *)
