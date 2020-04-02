(* Convention: i, j for string indices; x for suffix array indices.
   None of the functions assumes '$' terminated strings *)

let constructSA_slow s =
  let n = String.length s in
  let suffix i = String.sub s i (n - i) in
  let sa = Array.init (String.length s) (fun i -> i) in
  Array.sort (fun i j -> String.compare (suffix i) (suffix j)) sa;
  sa

(** [constructSA text] computes the suffix array of [text] in O(nlogn).
    [text] need not end with '$' *)
let constructSA text =
  let n = String.length text in
  let rank = Array.init (n + 1) (fun i -> if i = n then -1 else Char.code text.[i]) in
  let sa   = Array.init n (fun i -> i) in
  let tmp  = Array.make n 0 in
  let cnt_size  = max 256 (n + 1) in
  let cnt       = Array.make cnt_size 0 in
  let counting_sort k =
    Array.fill cnt 0 cnt_size 0;
    for i = 0 to n - 1 do
      let c = rank.(min n (i + k)) + 1 in
      cnt.(c) <- cnt.(c) + 1
    done;
    for c = 1 to cnt_size - 1 do
      cnt.(c) <- cnt.(c) + cnt.(c-1)
    done;
    for x = n - 1 downto 0 do
      let i = sa.(x) in
      let c = rank.(min n (i + k)) + 1 in
      cnt.(c) <- cnt.(c) - 1;
      tmp.(cnt.(c)) <- i
    done;
    Array.blit tmp 0 sa 0 n
  in
  let rec loop k =
    counting_sort k; counting_sort 0;
    tmp.(sa.(0)) <- 0;
    for x = 1 to n - 1 do
      let i, i' = sa.(x), sa.(x - 1) in
      let j, j' = min n (i + k), min n (i' + k) in
      if rank.(i) = rank.(i') && rank.(j) = rank.(j') then
        tmp.(i) <- tmp.(i')
      else tmp.(i) <- tmp.(i') + 1
    done;
    Array.blit tmp 0 rank 0 n;
    if rank.(sa.(n - 1)) < n - 1 then loop (2 * k) in
  loop 1;
  sa

let computeLCP_slow text sa =
  let n = String.length text in
  Array.init (n - 1) (fun x ->
    let i, j = sa.(x), sa.(x + 1) in
    let rec loop l =
      if max i j + l < n && text.[i + l] = text.[j + l] then
        loop (l + 1)
      else l in
    loop 0
  )

(** [computeLCP text sa] takes a string text and its suffix array sa,
    returns its LCP array, where [lcp.(x) = LCP(sa.(x), sa.(x+1))]. *)
let computeLCP text sa =
  let n = String.length text in
  let rank = Array.make n 0 in
  let lcp  = Array.make (n - 1) 0 in
  sa |> Array.iteri (fun x i -> rank.(i) <- x);
  let len = ref 0 in
  for i = 0 to n - 1 do
    if rank.(i) + 1 < n then begin
      let j = sa.(rank.(i) + 1) in
      while max i j + !len < n && text.[i + !len] = text.[j + !len] do
        incr len
      done;
      lcp.(rank.(i)) <- !len
    end;
    if !len > 0 then decr len
  done;
  lcp

let rec binary_search low high p =
  if low = high then
    if p low then low else raise Not_found
  else
    let mid = (low + high) / 2 in
    if p mid then
      binary_search low mid p
    else
      binary_search (mid + 1) high p

let string_matching text sa pattern =
  let n = String.length text in
  let m = String.length pattern in
  try
    let strcmp x =
      let i = sa.(x) in
      let rec loop l =
        if l = m then 0 else
        if i + l >= n then -1 else
        if text.[i + l] <> pattern.[l] then
          compare text.[i + l] pattern.[l]
        else loop (l + 1) in
      loop 0 in
    let lower_bound = binary_search 0 (n-1) (fun x -> strcmp x >= 0) in 
    if strcmp lower_bound > 0 then
      raise Not_found;
    if strcmp (n - 1) = 0 then Some (lower_bound, n) else
    let upper_bound = binary_search 0 (n-1) (fun x -> strcmp x > 0) in
    Some (lower_bound, upper_bound)
  with Not_found -> None

let lcs a b =
  let s = a ^ "#" ^ b in
  let in_a i = i < (String.length a) in
  let sa = constructSA s in
  let lcp = computeLCP s sa in
  let len, start = ref (-1), ref (-1) in
  for x = 0 to (Array.length lcp) - 1 do
    let i, j = sa.(x), sa.(x + 1) in
    if in_a i <> in_a j && lcp.(x) > !len then begin
      len := lcp.(x);
      start := i
    end
  done;
  String.sub s !start !len

let test () =
  let open Printf in
  let text = "ACGACGGCTGCGGTAACCC#TTACGGCTGCGGTCCCCTT@CCCCCCGTTTACGGCTGCGGTGG" in
  let sa = constructSA text in
  let lcp = computeLCP text sa in
  assert (sa = constructSA_slow text);
  assert (lcp = computeLCP_slow text sa);
  
  let (lrs_len, lrs_start) = (* Longest repeated substring *)
    lcp |> Array.mapi (fun i len -> (len, sa.(i))) |> Array.fold_left max (-1, -1) in
  printf "The LRS is '%s' with length = %d\n"
    (String.sub text lrs_start lrs_len) lrs_len;
  
  let pattern = "ACG" in
  (match string_matching text sa pattern with
    | Some (l, r) ->
      printf "'%s' found at" pattern;
      for x = l to r - 1 do printf " %d" sa.(x) done;
      printf "\n"
    | None ->
      printf "\"%s\" not found" pattern);
  
  let a, b = "Steven Halim", "Stephen Hawking" in
  printf "The LCS of '%s' and '%s' is '%s'\n" a b (lcs a b)
