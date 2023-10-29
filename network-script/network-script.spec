Name: network-script
Version: 1.0
Release: 2%{?dist}
Summary: it sets static ip for ethernet inferface
BuildArch: noarch
License: BSD-3-Clause-Clear
Source0: %{name}-%{version}.tar.gz

%description
This rpm install network script for to set static ip.

%prep
%setup -qn %{name}

%install
mkdir -p "$RPM_BUILD_ROOT/%{_sysconfdir}/sysconfig/network-scripts/"
cp ifcfg-eth1 "$RPM_BUILD_ROOT/%{_sysconfdir}/sysconfig/network-scripts/"

%files
%{_sysconfdir}/sysconfig/network-scripts/ifcfg-eth1
