open Printf

module RMQ = struct                                         (* Range Minimum Query *)
  type t =
    { l2: int array;
      a: int array;
      spt: int array array;
    }

  let init n a =
    let l2 = Array.make (n + 1) 0 in
    begin
      try
        for i = 0 to max_int do
          for j = 1 lsl i to 1 lsl (i + 1) - 1 do
            if j > n then raise Exit;
            l2.(j) <- i
          done
        done
      with Exit -> ()
    end;
    let l2_n = l2.(n) in
    (* initialization *)
    let spt = Array.make_matrix (l2_n + 1) n 0 in
    spt.(0) <- Array.init n (fun i -> i);               (* RMQ of sub array [j..j] *)

    (* the two nested loops below have overall time complexity = O(n log n) *)
    for i = 1 to l2_n do                     (* for each i s.t. 2^i <= n, O(log n) *)
      for j = 0 to n - 1 lsl i do                        (* for each valid j, O(n) *)
        let x = spt.(i-1).(j) in                            (* covers [j..j+2^i-1] *)
        let y = spt.(i-1).(j + 1 lsl (i-1)) in  (* covers [j+(1<<(i-1))..j+(1<<i)] *)
        spt.(i).(j) <- if a.(x) <= a.(y) then x else y
      done
    done;
    {l2; a; spt}

  let query i j {l2; a; spt} =
    let k = l2.(j - i + 1) in                                    (* 2^k <= (j-i+1) *)
    let x = spt.(k).(i) in                                  (* covers [i..i+2^k-1] *)
    let y = spt.(k).(j - 1 lsl k + 1) in                    (* covers [j-2^k+1..j] *)
    if a.(x) <= a.(y) then x else y
end

let () =
  (* same example as in chapter 2: segment tree *)
  let a = [|18; 17; 13; 19; 15; 11; 20|] in
  let n = Array.length a in
  let rmq = RMQ.init n a in
  for i = 0 to n - 1 do
    for j = i to n - 1 do
      printf "RMQ(%d, %d) = %d\n" i j (RMQ.query i j rmq)
    done
  done
