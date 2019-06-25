open Printf
open Scanf

let () =
  let first = ref true in
  try
    while true do
      let k = scanf "%d " (fun x -> x) in
      if k = 0 then raise Exit;
      if not !first then printf "\n";
      first := false;
      let s = Array.init k (fun _ -> scanf "%d " (fun x -> x)) in
      for a = 0 to k-6 do
        for b = a+1 to k-5 do
          for c = b+1 to k-4 do
            for d = c+1 to k-3 do
              for e = d+1 to k-2 do
                for f = e+1 to k-1 do
                  printf "%d %d %d %d %d %d\n" s.(a) s.(b) s.(c) s.(d) s.(e) s.(f);
                done
              done
            done
          done
        done
      done
    done
  with Exit ->
    ()
