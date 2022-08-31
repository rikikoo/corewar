.name		"Carnage"
.comment	"this is freedom!"

mark:
	live %510
	ld %-11, r2
	sti r1, %0, r2
	and %0, %0, r3

live:
	zjmp %:mark
