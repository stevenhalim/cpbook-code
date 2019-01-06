open Printf

let lower_bound x a n =
  let rec aux l r =
    if l >= r then l
    else
      let m = (l+r) / 2 in
      if a.(m) >= x then
        aux l m
      else
        aux (m+1) r
  in
  aux 0 n

let print_array s a n =
  for i = 0 to n-1 do
    if i = 0 then printf "%s: [" s
    else printf ", ";
    printf "%d" a.(i)
  done;
  printf "]\n"

let reconstruct_print e a p =
  let x = ref e in
  let s = Stack.create () in
  while p.(!x) >= 0 do
    Stack.push a.(!x) s;
    x := p.(!x)
  done;
  printf "[%d" a.(!x);
  while not (Stack.is_empty s) do
    printf ", %d" (Stack.pop s)
  done;
  printf "]\n"

let () =
  let a = [|-7; 10; 9; 2; 3; 8; 8; 1; 2; 3; 4|] in
  let n = Array.length a in
  let l = Array.make n 0 in
  let l_id = Array.make n 0 in
  let p = Array.make n 0 in

  let lis = ref 0 in
  let lis_end = ref 0 in
  for i = 0 to n-1 do
    let pos = lower_bound a.(i) l !lis in
    l.(pos) <- a.(i);
    l_id.(pos) <- i;
    p.(i) <- if pos > 0 then l_id.(pos-1) else -1;
    if pos+1 > !lis then begin
      lis := pos+1;
      lis_end := i;
    end;

    printf "Considering element a.(%d) = %d\n" i a.(i);
    printf "LIS ending at a.(%d) is of length %d: " i (pos+1);
    reconstruct_print i a p;
    print_array "l is now" l !lis;
    printf "\n"
  done;

  printf "Final LIS is of length %d: " !lis;
  reconstruct_print !lis_end a p
