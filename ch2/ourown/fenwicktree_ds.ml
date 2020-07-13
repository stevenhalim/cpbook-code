open Printf

module FenwickTree = struct
  type t = { ft : int array }                    (* internal FT is an array *)

  let lsone s = s land -s                        (* the key operation *)

  let init m f =
    let ft = Array.make (m + 1) 0 in             (* create an empty FT *)
    for i = 1 to m do                            (* O(m) *)
      ft.(i) <- ft.(i) + f (i - 1);              (* add this value *)
      let i' = i + lsone i in
      if i' <= m then                            (* i has parent *)
        ft.(i') <- ft.(i') + ft.(i)              (* add to that parent *)
    done;
    {ft}

  let make m =
    init m (fun _ -> 0)

  let rsq {ft} j =                               (* returns RSQ(1, j) *)
    let rec go j sum =
      if j = 0 then sum
      else go (j - lsone j) (sum + ft.(j))
    in
    go j 0

  let rsq2 ft i j =
    rsq ft j - rsq ft (i - 1)                    (* inc/exclusion *)

  (* updates value of the i-th element by v (v can be +ve/inc or -ve/dec) *)
  let update {ft} i v =
    let rec go i =
      if i < Array.length ft then (
        ft.(i) <- ft.(i) + v;
        go (i + lsone i)
      )
    in
    go i

  let select {ft} k =                            (* O(log m) *)
    let rec go p =
      if p * 2 >= Array.length ft then p
      else go (p * 2)
    in
    let p = go 1 in
    let rec go p k i =
      if p = 0 then i
      else if k > ft.(i + p) then
        go (p / 2) (k - ft.(i + p)) (i + p)
      else
        go (p / 2) k i
    in
    go p k 0 + 1
end

module RUPQ = struct                             (* RUPQ variant *)
  type t = { ft : FenwickTree.t }                (* internally use PURQ FT *)

  let make m =
    { ft = FenwickTree.make m }

  let range_update {ft} ui uj v =
    FenwickTree.update ft ui v;                  (* [ui, ui+1, .., m] +v *)
    FenwickTree.update ft (uj + 1) (-v)          (* [uj+1, uj+2, .., m] -v *)
                                                 (* [ui, ui+1, .., uj] +v *)
  let point_query {ft} i =
    FenwickTree.rsq ft i
end

module RURQ = struct                             (* RURQ variant *)
  type t =                                       (* needs two helper FTs *)
    { rupq : RUPQ.t                              (* one RUPQ and *)
    ; purq : FenwickTree.t                       (* one PURQ *)
    }

  let make m =
    { rupq = RUPQ.make m
    ; purq = FenwickTree.make m
    }

  let range_update {rupq; purq} ui uj v =
    RUPQ.range_update rupq ui uj v;              (* [ui, ui+1, .., uj] +v *)
    FenwickTree.update purq ui (v * (ui - 1));   (* -(ui-1)*v before ui *)
    FenwickTree.update purq (uj + 1) (-v * uj)   (* +(uj-ui+1)*v after uj *)

  let rsq {rupq; purq} j =
    RUPQ.point_query rupq j * j - FenwickTree.rsq purq j

  let rsq2 rurq i j =
    rsq rurq j - rsq rurq (i - 1)
end

let () =
  let f = [|0; 1; 0; 1; 2; 3; 2; 1; 1; 0|] in
  let ft = FenwickTree.init (Array.length f) (fun i -> f.(i)) in
  printf "%d\n" (FenwickTree.rsq2 ft 1 6); (* 7 => ft[6]+ft[4] = 5+2 = 7 *)
  printf "%d\n" (FenwickTree.select ft 7); (* index 6, rsq(1, 6) == 7, which is >= 7 *)
  FenwickTree.update ft 5 1; (* update demo *)
  printf "%d\n" (FenwickTree.rsq2 ft 1 10); (* now 12 *)
  printf "=====\n";
  let rupq = RUPQ.make 10 in
  let rurq = RURQ.make 10 in
  RUPQ.range_update rupq 2 9 7; (* indices in [2, 3, .., 9] updated by +7 *)
  RURQ.range_update rurq 2 9 7; (* same as rupq above *)
  RUPQ.range_update rupq 6 7 3; (* indices 6&7 are further updated by +3 (10) *)
  RURQ.range_update rurq 6 7 3; (* same as rupq above *)
  (* idx = 0 (unused) | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10
   * val = -          | 0 | 7 | 7 | 7 | 7 |10 |10 | 7 | 7 | 0 *)
  for i = 1 to 10 do
    printf "%d -> %d\n" i (RUPQ.point_query rupq i)
  done;
  printf "RSQ(1, 10) = %d\n" (RURQ.rsq2 rurq 1 10); (* 62 *)
  printf "RSQ(6, 7) = %d\n" (RURQ.rsq2 rurq 6 7); (* 20 *)
