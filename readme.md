# HTTP Server Benchmark

```
wrk -t8 -c1000 -d10s http://localhost:8080
```

## Vibe - D

### Setup
```
dub run --compiler=ldc2 --build=release
```

### Manual memory management

```
Running 10s test @ http://localhost:8080
  8 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     5.02ms    4.54ms 170.69ms   88.86%
    Req/Sec    25.27k     3.47k   46.09k    72.85%
  2008302 requests in 10.06s, 333.26MB read
Requests/sec: 199566.09
Transfer/sec:     33.12MB
```

### GC

```
Running 10s test @ http://localhost:8080
  8 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stde
    Latency     9.07ms   28.92ms 513.57ms   98.21%
    Req/Sec    22.05k     4.15k   37.00k    80.66%
  1748422 requests in 10.05s, 290.13MB read
Requests/sec: 173900.30
Transfer/sec:     28.86MB

```

## Actix - Rust

### Setup

```
git clone https://github.com/actix/examples
cd examples/basics
cargo run --release
```

```
Running 10s test @ http://localhost:8081
  8 threads and 1000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     4.22ms    4.42ms  45.49ms   87.34%
    Req/Sec    34.53k     8.64k   72.10k    65.70%
  2748992 requests in 10.09s, 547.92MB read
Requests/sec: 272326.85
Transfer/sec:     54.28MB
```
