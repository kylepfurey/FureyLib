;; .wat
;; Program Main Entry Point Script

(module
  ;; JavaScript imports.
  (import "env" "log" (func $log (param i32 i32)))

  ;; Memory page for data.
  (memory (export "memory") 1)

  ;; Strings.
  (data (i32.const 0) "Hello, Dinner!\n")

  ;; Entry point of the program.
  (func $main (export "main")
    i32.const 0   ;; Push pointer to string
    i32.const 15  ;; Push size of string
    call $log     ;; Call log
    ;; New code here
  )

  ;; Call main().
  (start $main)
)
