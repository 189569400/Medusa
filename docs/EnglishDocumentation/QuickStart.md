## Demo

![Bashdemo](https://github.com/Ascotbe/Image/blob/master/Medusa/demo.gif?raw=true)

## Parameters

| Command | Number of parameters | Effect                                                       | Annotation                                                   |
| ------- | -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| -u      | 1                    | Input single url（Use `http://` or `https://` first better than none, do not use any paremeters follow the url | example : `-u https://www.ascotbe.com` or `-u https://192.168.0.1` |
| -a      | 1                    | Specify header files or use random headers                   | When using this feature, please refer to the documentation for this content |
| -f      | 1                    | The filename includes urls that want to scan.                | `-u` or `-f` must exists one and only one                    |
| -p      | 1                    | You need to fill in the IP of your proxy, if you have a port you need to bring the port | to use BURP as a proxy then you should pass in 127.0.0.1:8080 |
| -m      | 1                    | Scan for single module,such as: Struts2 or Apache, etc.      | The specific content can be entered by the corresponding name in the project Modules folder. |
| -t      | 1                    | Processes usage setting, default(-t 5)                       | None                                                         |
| -s      | 1                    | Enable subdomain detection                                   |                                                              |
| -PL     | 1                    | Ports in list form                                           | As long as they are separated by non-numbers, ports exceeding 65535 will be eliminated. If -p or -P is not output, the default port will be scanned. eg: 22,139,445,3389 |
| -PR     | 1                    | Ports in the form of ranges                                  | As long as they are separated by non-digits, ports exceeding 65535 will be eliminated. If -p or -P is not output, the default port will be scanned. eg:1-65535 |

##  Environment configuration

### System environment configuration

> Ubuntu

The `JAVA` environment needs to be installed and the `java` command can be executed in the global variables

> CentOS

1.The `JAVA` environment needs to be installed and the `java` command can be executed in the global variables

2.You need to execute the `yum install sqlite*` command to install the **sqlite3.so** library

> Mac OS

The `JAVA` environment needs to be installed and the `java` command can be executed in the global variables

### Install Python env

The current plug-in is developed under the `Python3.7.x` environment. Below` 3.7`, some functions cannot be used. If you need to use a scanner or write a plug-in, you must first install the `Python` development environment. It is recommended to use` PyCharm` + `Anaconda` as development environment.

### Install dependencies

The packages needed to run Medusa are executed in the root directory

```python
pip install -r Medusa.txt
```


## Configuration file

The configuration file referred to in this section is the same file

#### 0x01 DNSLOG

Since the `DNSLOG` I built does not support certain protocols, there are currently two methods for detecting third-party platforms

> The first method (by default)

The first is the default method, no need to modify, convenient and fast

> The second method

Use `DNSLOG` in http://ceye.io/, this method needs to modify the configuration file

```
#Open this file in the root directory (Medusa directory)
vim config.py
```

Change `ceye_dnslog_url` and`ceye_dnslog_key` to the values of your `Identifier` and` API Token` at http://ceye.io/ , Then change `dnslog_name` to `ceye`

**Note: **When using the script, ensure that the network is unblocked. If the vulnerability is not scanned, you may wish to see if the `DNSLOG` data exists

#### 0x02 Debug mode 

This mode is closed by default. If you need to open it, please modify the parameters in the `config.py` file

```
#Default
debug_mode = False
#Turn on Debug mode
debug_mode = True
```

The output content of this mode is not the progress bar and module loading content, but has become the error message of each plugin


#### 0x03 Multithreading

Because the refactoring replaces the previous multi-threads with multi-processes, the for loop in a single plugin is replaced with multi-threads, so the default number of threads is **15**. If you need to modify, change the value of `thread_number` in the configuration file to The number of threads you need

```
thread_number=15 #Default number of threads
```



## Quick start

The tool is still in the testing stage. If you have any questions, please submit `issues`. Remember, this scanner is only use for authorized testing

#### 0x01 Use the scanner to scan a single website

Note: It is recommended to put the complete path, some plugins need to use the full path name, for example: `Struts2`

```bash
python3 MedusaScan.py -u https://www.ascotbe.com
```

#### 0x02 Use the scanner to scan a batch of websites

`Ascotbe.txt` is the file you store. It is best to put it in the same directory as the` MedusaScan.py` file. The file format you store `URL` is one` url` per line

Documents need to pay attention to several specifications

- Need to fill in `url` and one` url` per line

- `url` needs to bring` http:// `or` https:// `, if both protocols need to be scanned it can be written in two lines

- If different ports in a single `url` correspond to different services, you need to write them. For example, **8080** and **1024** correspond to different services, and if you want to scan all, you need to press the following Written in the form

  ```
  http://ascotbe.com:1024/test
  http://ascotbe.com:8080/test
  ```

- Different subdirectories, such as `test` and` medusa`, also need to be written on separate branches

  ```
  http://ascotbe.com:1024/test
  http://ascotbe.com:1024/medusa
  ```

Next run the following command to start scanning

```bash
python3 MedusaScan.py -f Ascotbe.txt #Your files are best placed in the same level as MedusaScan
```

#### ~~0x03 Link crawling in JavaScript on the target website~~

This function is commented because not very useful now

```bash
python3 MedusaScan.py -u https://www.ascotbe.com -j
```

#### ~~0x04 Collect subdomains for the target website~~

Close temporarily and wait for reconstruction

~~The scan result is in the `ScanResult` directory, only the domain name is supported and the **IP** form is not supported~~

```bash
python3 MedusaScan.py -u https://www.ascotbe.com -s
```

#### 0x05 HTTP request related configuration

Need to be configured in the **config.py** configuration file

```bash
#########################################################################
#requests configuration
#########################################################################
user_agent_randomization=False#Whether to enable randomization in headers, it is disabled by default
user_agent_browser_type="chrome"#Currently, only the following browsers are supported. Modification to other browsers may result in unavailability.
                                #firefox、ie、msie、opera、chrome、AppleWebKit、Gecko、safari
#Default request header, which saves necessary data, User-Agent header data will change if randomization is enabled
# WEB version add a judgment, if the user passes in a header, the header will be overwritten
headers={
    "Connection": "close",
    "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 11_0_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36",
    "Accept": "*/*",
    "Accept-Encoding": "gzip, deflate",
    "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8",
    "dnt": "1"
}
#If you don’t want to use a proxy, replace the following parameters with:proxies=None
proxies = {
  "http": "http://127.0.0.1:8080",
  "https": "https://127.0.0.1:8080",
}
```

#### 0x06 Scanning for single modules

Please use the name supported by the module for the root folder. A folder name corresponds to a module, and please pay attention to capitalization. It is really incomprehensible. Please refer to [in this file](https://www.ascotbe.com/Medusa/Documentation/#/PluginDirectory) name

```bash
python3 MedusaScan.py -u https://www.ascotbe.com -m Struts2
```

#### 0x07 Processes setting

Turn on the multi-process function, the default is 15 processes, the more processes, the faster, when a plugin uses the for loop, it will start multi-threading in the process!

```bash
python3 MedusaScan.py -u https://www.ascotbe.com -t 100 #100 processes
```

#### 0x09 sensitive information leakage

Integrated into the module, the full scan is automatically started, if you need to scan separately, you only need to enter the module name

## Result

1. The output `The number of vulnerabilities scanned was: 0` means that the vulnerability was not scanned

2. There are no other files in the `ScanResult` directory except `Medusa.txt`

3. There is no new content in the `Medusa.db` file, or the file is not created

4. If none of the above three points exist, it means that no loopholes really have been found

