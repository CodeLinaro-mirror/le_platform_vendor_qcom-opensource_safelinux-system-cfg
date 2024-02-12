Name: early-ethernet
Version: 1.0
Release: r0
Summary: systemd service file to enable early ethernet mode
License: BSD-3-Clause-Clear
URL: https://www.codelinaro.org/
Source0: %{name}-%{version}.tar.gz
BuildRequires: systemd systemd-rpm-macros
%{?systemd_requires}
Requires: net-tools systemd

%description
%{name} - %{summary}

%prep
%setup -n %{name}

%install
mkdir -p %{buildroot}%{_unitdir}
install -DpZm 0644 early_eth0.service %{buildroot}%{_unitdir}
install -DpZm 0644 early_eth1.service %{buildroot}%{_unitdir}

%post
systemctl enable early_eth0.service
systemctl enable early_eth1.service

%preun
%systemd_preun early_eth0.service
%systemd_preun early_eth1.service

%postun
%systemd_postun_with_restart early_eth0.service
%systemd_postun_with_restart early_eth1.service

%files
%{_unitdir}/early_eth0.service
%{_unitdir}/early_eth1.service

