<img align="right" src="https://github.com/jafarlihi/file-hosting/blob/8e69dc688584288ea170ece7aee96b879e46c27e/sysm.png?raw=true">

# sysm

sysm (**sys**tem **m**usic) lets you configure specific sounds to be played on any arbitrary internal system event or an external event. This can give you visibility into your system while you are working (such as CPU/RAM/disk/network usage, audit events, etc.) without taking up space in your screen or notifications about external events such as something changing in some arbitrary website.

## Concepts

Rules require you to specify one "source" and one "type".

"source" is basically the information source, where the data will be fetched from, such as "shell_source" (runs an arbitrary shell command and returns the output), "file_column" (fetches specified column from a file), etc.

"type" controls how and when the audio will be played, for example "on_threshold_cross" (when value crosses given threshold), "on_match_when_past_no_match" (when value matches given regex pattern when it didn't match it last tick), "while_delta_above_threshold" (while delta between last tick's value and current value is above given threshold), etc.

New types and sources can be added by subclassing `Source` and `Type`. Contributions are welcome!

## Installation

Install the SFML dependency:

- Arch Linux:
```
sudo pacman -S sfml
```

- Ubuntu:
```
sudo apt install libsfml-dev
```

Build & install:
```
make install
```

Run:
```
./sysm.elf &
```

## Configuration

Sample config:
```
[high_disk_write_speed]
enabled = true
description = "While current disk write speed is above threshold"
sleep = 1000
start_music = "~/.config/sysm/audio/processing_1_start.wav"
content_music = "~/.config/sysm/audio/processing_1.wav"
end_music = "~/.config/sysm/audio/processing_1_end.wav"
content_music_volume = 75
source = file_column
file = "/sys/block/sda/stat"
column = 6
type = while_delta_above_threshold
threshold = 5000

[high_cpu_usage]
enabled = true
description = "When current CPU usage crosses above threshold"
sleep = 3000
content_music = "~/.config/sysm/audio/beeps_1.wav"
source = shell
command = "awk '{u=$2+$4; t=$2+$4+$5; if (NR==1){u1=u; t1=t;} else print int(($2+$4-u1) * 100 / (t-t1)); }' <(grep 'cpu ' /proc/stat) <(sleep 1;grep 'cpu ' /proc/stat)"
type = on_threshold_cross
threshold = 90

[any_conn_estab_for_first_time]
enabled = true
description = "When any network connection establishes when no network connection exists"
sleep = 1000
content_music = "~/.config/sysm/audio/connection_established_1.wav"
content_music_volume = 25
source = shell
command = "ss -atun4 | grep ESTAB"
type = on_match_when_past_not_match
match = ".*\S.*"

[specific_ip_conn_estab_for_first_time]
enabled = true
description = "When specified IP network connection establishes when it didn't exist before"
sleep = 1000
content_music = "~/.config/sysm/audio/connection_established_1.wav"
content_music_volume = 25
source = shell
command = "ss -atun4 | grep ESTAB | grep 192.168.23.2"
type = on_match_when_past_not_match
match = ".*\S.*"

[github_star_received]
enabled = false
description = "When someone stars one of your repositories"
sleep = 10000
content_music = "~/.config/sysm/audio/beeps_2.wav"
source = shell
command = "TODO"
type = on_value_change
```
