open Printf
open Scanf

let () =
  let n = scanf "%d\n" (fun x -> x) in
  let a = Array.make_matrix (n + 1) n 0 in
  for i = 1 to n do
    for j = 0 to n - 1 do
      let x = scanf "%d " (fun x -> x) in
      a.(i).(j) <- x + a.(i - 1).(j)
    done
  done;
  let max_sub_rect = ref (-127_00_00) in
  for u = 0 to n - 1 do
    for d = u + 1 to n do
      let sub_rect = ref 0 in
      for row = 0 to n - 1 do
        sub_rect := !sub_rect + a.(d).(row) - a.(u).(row);
        if !sub_rect < 0 then sub_rect := 0;
        max_sub_rect := max !max_sub_rect !sub_rect
      done
    done
  done;
  printf "%d\n" !max_sub_rect

(* let () =
 *   let n = scanf "%d\n" (fun x -> x) in
 *   let a = Array.make_matrix (n + 1) (n + 1) 0 in
 *   for i = 1 to n do
 *     for j = 1 to n do
 *       let x = scanf "%d " (fun x -> x) in
 *       a.(i).(j) <- x + a.(i - 1).(j) + a.(i).(j - 1) - a.(i - 1).(j - 1)
 *     done
 *   done;
 *   let max_sub_rect = ref (-127_00_00) in
 *   for i = 0 to n - 1 do
 *     for j = 0 to n - 1 do
 *       for k = i + 1 to n do
 *         for l = j + 1 to n do
 *           let sub_rect = a.(i).(j) - a.(i).(l) - a.(k).(j) + a.(k).(l) in
 *           max_sub_rect := max !max_sub_rect sub_rect
 *         done
 *       done
 *     done
 *   done;
 *   printf "%d\n" !max_sub_rect *)

(* let () =
 *   let n = scanf "%d\n" (fun x -> x) in
 *   let a =
 *     Array.init n @@ fun _ ->
 *     Array.init n @@ fun _ ->
 *     scanf "%d " (fun x -> x)
 *   in
 *   let max_sub_rect = ref (-127_00_00) in
 *   for i = 0 to n - 1 do
 *     for j = 0 to n - 1 do
 *       for k = i to n - 1 do
 *         for l = j to n - 1 do
 *           let sub_rect = ref 0 in
 *           for a' = i to k do
 *             for b = j to l do
 *               sub_rect := !sub_rect + a.(a').(b)
 *             done
 *           done;
 *           max_sub_rect := max !max_sub_rect !sub_rect
 *         done
 *       done
 *     done
 *   done;
 *   printf "%d\n" !max_sub_rect *)
