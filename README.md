# Some basic useful tools for lazzzy hackers

If you ever get tired of typing out repetitive recon commands then this is for you.
Example:
```bash
#This could be used to get a list of users
cat /etc/passwd  | awk -F \":\" {'print $1'}
```
With is status command it becomes:
```bash
./status sudo
```

