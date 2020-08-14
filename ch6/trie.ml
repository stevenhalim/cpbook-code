module Trie = struct
  type trie = {
    mutable exist : bool;
    children: trie option array
  }

  let make_empty () = { exist = false; children = Array.make 26 None }

  let to_int_seq str = String.to_seq str |> Seq.map (fun c -> int_of_char c - int_of_char 'A')

  let insert word trie =
    let rec aux trie = function
      | Seq.Nil ->
        trie.exist <- true
      | Seq. Cons (c, tl) ->
        match trie.children.(c) with
        | None ->
          let node = make_empty () in
          trie.children.(c) <- Some node;
          aux node (tl ())
        | Some child ->
          aux child (tl ())
        in
    aux trie (to_int_seq word ())

  let search word trie =
    let rec aux trie = function
      | Seq.Nil -> trie.exist
      | Seq. Cons (c, tl) ->
        match trie.children.(c) with
        | None ->
          false
        | Some child ->
          aux child (tl ())
        in
    aux trie (to_int_seq word ())

  let starts_with prefix trie =
    let rec aux trie = function
      | Seq.Nil -> true
      | Seq. Cons (c, tl) ->
        match trie.children.(c) with
        | None ->
          false
        | Some child ->
          aux child (tl ())
        in
    aux trie (to_int_seq prefix ())
end

let () =
  let trie = Trie.make_empty () in
  let open Printf in
  ["CAR"; "CAT"; "RAT"] |> List.iter (fun s -> Trie.insert s trie);
  printf "%b\n" (Trie.search "CAR" trie);
  printf "%b\n" (Trie.search "DOG" trie);
  printf "%b\n" (Trie.starts_with "CA" trie);
  printf "%b\n" (Trie.starts_with "Z" trie);
  printf "%b\n" (Trie.starts_with "AT" trie);
