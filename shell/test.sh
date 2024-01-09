slot_total=$1
port_total=$(lspci |awk '{print $3}' | grep 0200 | wc -l)
named_port_total=$(ifconfig -a |grep -E "eth|ge" | wc -l)

if [ $port_total -gt $named_port_total ]; then
    echo "not named all port"
    exit 1
fi

