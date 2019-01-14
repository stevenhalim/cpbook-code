open Printf

let gaussian_elimination n aug =
  for i = 0 to n - 1 do                 (* the forward elimination phase *)
    let l = ref i in
    for j = i + 1 to n - 1 do      (* which row has largest column value *)
      if abs_float aug.(j).(i) > abs_float aug.(!l).(i) then
        l := j;                                   (* remember this row l *)
    done;
    (* swap this pivot row, reason: minimize floating point error *)
    let t = aug.(i) in aug.(i) <- aug.(!l); aug.(!l) <- t;
    for j = i + 1 to n - 1 do    (* the actual forward elimination phase *)
      for k = n downto i do
        aug.(j).(k) <- aug.(j).(k) -. aug.(i).(k) *. aug.(j).(i) /. aug.(i).(i)
      done
    done
  done;

  let ans = Array.create_float n in       (* the back substitution phase *)
  for j = n - 1 downto 0 do                           (* start from back *)
    let t = ref 0. in
    for k = j + 1 to n - 1 do
      t := !t +. aug.(j).(k) *. ans.(k)
    done;
    ans.(j) <- (aug.(j).(n) -. !t) /. aug.(j).(j)  (* the answer is here *)
  done;
  ans

let () =
  let aug = [|
    [|1.; 1.; 2.; 9.|];
    [|2.; 4.; -3.; 1.|];
    [|3.; 6.; -5.; 0.|];
  |] in
  let x = gaussian_elimination 3 aug in
  printf "X = %.1f, Y = %.1f, Z = %.1f\n" x.(0) x.(1) x.(2)
