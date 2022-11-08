# generate load
for i in 1 2 3 4; do while : ; do : ; done & done

# kill process
for i in 1 2 3 4; do kill %$i; done