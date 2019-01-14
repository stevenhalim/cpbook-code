open Printf
open Scanf

let () =
  let n = scanf "%d\n" (fun x -> x) in
  for _ = 1 to n do
    let a, b, c = scanf "%d %d %d\n" (fun a b c -> a, b, c) in
    try
      (* for x = -100 to 100 do
       *   for y = -100 to 100 do
       *     for z = -100 to 100 do
       *       if y <> x && z <> x && z <> y  (\* all three must be different *\)
       *          && x + y + z = a
       *          && x * y * z = b
       *          && x * x + y * y + z * z = c
       *       then begin
       *         printf "%d %d %d\n" x y z;
       *         raise Exit
       *       end
       *     done
       *   done
       * done; *)
      for x = -100 to 100 do
        for y = -100 to 100 do
          if y <> x && x * x + y * y <= c then
            for z = -100 to 100 do
              if z <> x && z <> y
                 && x + y + z = a
                 && x * y * z = b
                 && x * x + y * y + z * z = c
              then begin
                printf "%d %d %d\n" x y z;
                raise Exit
              end
            done
        done
      done;
      printf "No solution.\n"
    with Exit -> ()
  done
