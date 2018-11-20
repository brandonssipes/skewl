target triple = "x86_64-pc-linux-gnu"
@pfmt = constant [5 x i8] c"%ld\0A\00"
declare i32 @printf(i8*,...)
declare i32 @scanf(i8*,...)
define i32 @main() {
    call i32(i8*,...) @printf(i8* getelementptr([5 x i8], [5 x i8]* @pfmt, i32 0, i32 0), i64 5)
    ret i32 0
}
