num=`df -h | tail -n 1 | awk '{split($0, a, " "); print a[5]}' | sed 's/%//g'`
printf "%-7s%2s%s\n" "before" $num "%"

rm -rf ~/Library/Application\ Support/Code
rm -rf ~/Library/Caches
rm -rf ~/Library/Containers
mkdir -p ~/Library/Application\ Support/Code/User
cp settings.json ~/Library/Application\ Support/Code/User/

num2=`df -h | tail -n 1 | awk '{split($0, a, " "); print a[5]}' | sed 's/%//g'`
printf "%-7s%2s%s\n" "after" $num2 "%"
tot=$(($num-$num2))
printf "%-7s%2s%s\n" "freed" $tot "%"

42dark
