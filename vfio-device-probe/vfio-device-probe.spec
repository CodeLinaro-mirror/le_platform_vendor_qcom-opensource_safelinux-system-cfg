Name: vfio-device-probe
Version: 1.0
Release: 2%{?dist}
Summary: Install vfio systemd service file and bind script
BuildArch: noarch
License: BSD-3-Clause-Clear
Source0: %{name}-%{version}.tar.gz

Requires: systemd
BuildRequires: systemd systemd-rpm-macros
%{?systemd_requires}

%global _vfiobinddir /usr/lib/vfio-bind.d/

%description
This rpm contians vfio systemd service file and bind script.

%prep
%setup -qn %{name}

%install
mkdir -p %{buildroot}%{_bindir}
mkdir -p %{buildroot}%{_unitdir}
install -m 777 vfio-device-bind.sh %{buildroot}%{_bindir}
install -D -m 777 vfio-device-probe.service %{buildroot}%{_unitdir}
install -DpZm 0644 sa8775_dev.conf %{buildroot}%{_vfiobinddir}/sa8775_dev.conf

%post
systemctl enable vfio-device-probe.service
%{_bindir}/vfio-device-bind.sh

%files
%{_bindir}/vfio-device-bind.sh
%{_unitdir}/vfio-device-probe.service
%{_vfiobinddir}/sa8775_dev.conf
