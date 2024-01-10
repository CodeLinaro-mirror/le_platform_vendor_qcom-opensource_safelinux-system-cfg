Name: extra-tools
Version: 1.0
Release: r0
Summary: extra-tools RPMs
License: BSD-3-Clause-Clear
URL: https://www.codelinaro.org/
Source0: %{name}-%{version}.tar.gz

Requires: ethtool iperf3 iproute-tc tcpdump
Requires: stress-ng libtirpc perf sysstat

%description
%{name} - %{summary} - meta package that pulls in many extra tools RPMs

# We must set debug_package to nil because there are no "source code" files to
# create debug symbols from.
%global debug_package %{nil}

%prep
%setup -n %{name}

%files
