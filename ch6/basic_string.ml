open Printf

let counter words =
  let freq = Hashtbl.create 16 in
  words |> List.iter (fun word ->
    if not (Hashtbl.mem freq word) then Hashtbl.add freq word 0
    else let cnt = Hashtbl.find freq word in Hashtbl.replace freq word (cnt + 1));
  freq

let count string c =
  string |> String.to_seq |> Seq.fold_left (fun acc x ->
    if x = c then acc + 1 else acc) 0

let () =
  let oneline =
    let rec first_block () =
      let line = read_line () in
      if line = "......." then []
      else line :: first_block ()
    in
    first_block ()
      |> String.concat " "
      |> Str.global_replace (Str.regexp_string "- ") ""
      |> String.lowercase_ascii
  in
  let last_line = read_line () in
  let ndigits, nvowels, nconsonants =
    oneline |> String.to_seq |> Seq.fold_left (fun (x, y, z) ->
      function
      | '0' .. '9' -> (x + 1, y, z)
      | 'a' .. 'z' as c ->
        if String.contains "aeiou" c then (x, y + 1, z)
        else (x, y, z + 1)
      | _ -> (x, y, z)
    ) (0, 0, 0)
  in
  let words = oneline |> Str.split (Str.regexp "\\( \\|\\.\\|,\\)+") in
  let freq = counter words in

  printf "%s\n" oneline;
  printf "%d %d %d\n" ndigits nvowels nconsonants;
  printf "%s %s\n"
    (List.fold_left min (List.hd words) words)
    (List.fold_left max (List.hd words) words);
  printf "%d\n" (if Hashtbl.mem freq "cs3233" then 1 else 0);
  printf "%d %d %d\n"
    (count last_line 's') (count last_line 'h') (count last_line '7')
