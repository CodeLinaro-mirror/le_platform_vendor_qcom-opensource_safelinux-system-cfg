# SPDX-License-Identifier: BSD-3-Clause-Clear
# Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.

Name: irqbalance-config
Version: 1.0
Release: r0
Summary: irqbalance-config RPM
License: BSD-3-Clause-Clear
URL: https://www.codelinaro.org
Source0:%{name}-%{version}.tar.gz

Requires: systemd irqbalance

%description
irqbalance config & policy script

%prep
%autosetup -n %{name}-%{version}

%install
mkdir -p %{buildroot}%{_bindir}
install -D -m 744 set_irq_bal_level.sh %{buildroot}%{_bindir}
install -D -m 744 irqbal_args_update.sh %{buildroot}%{_bindir}

%post
/usr/bin/irqbal_args_update.sh
systemctl enable irqbalance.service

%files
%{_bindir}/set_irq_bal_level.sh
%{_bindir}/irqbal_args_update.sh
