open Printf

let () =
  let mapper = Hashtbl.create 10 in
  let used_values = Hashtbl.create 10 in

  (* suppose we enter these 7 name-score pairs below *)
  (*
  john 78
  billy 69
  andy 80
  steven 77
  felix 82
  grace 75
  martin 81
  *)
  Hashtbl.add mapper "john"   78; Hashtbl.add used_values 78 ();
  Hashtbl.add mapper "billy"  69; Hashtbl.add used_values 69 ();
  Hashtbl.add mapper "andy"   80; Hashtbl.add used_values 80 ();
  Hashtbl.add mapper "steven" 77; Hashtbl.add used_values 77 ();
  Hashtbl.add mapper "felix"  82; Hashtbl.add used_values 82 ();
  Hashtbl.add mapper "grace"  75; Hashtbl.add used_values 75 ();
  Hashtbl.add mapper "martin" 81; Hashtbl.add used_values 81 ();

  (* then the internal content of mapper/used_values are not really known
   * (implementation dependent) *)

  (* iterating through the content of mapper will give a jumbled output
   * as the keys are hashed into various slots *)
  mapper |> Hashtbl.iter (fun key value ->
      printf "%s %d\n" key value;
    );

  (* map can also be used like this *)
  printf "steven's score is %d, grace's score is %d\n"
    (Hashtbl.find mapper "steven") (Hashtbl.find mapper "grace");
  printf "==================\n";

  (* there is no lower_bound and upper_bound in an unordered_map *)

  (* O(1) search, found *)
  printf "%d\n" (Hashtbl.find used_values 77; 77);
  (* O(1) search, not found *)
  if Option.is_none (Hashtbl.find_opt used_values 79) then
    printf "79 not found\n";
