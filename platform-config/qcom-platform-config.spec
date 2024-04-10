Name: qcom-platform-config
Version: 1.0
Release: r0
Summary: configures systemd for qcom platforms
License: BSD-3-Clause-Clear
URL: https://www.codelinaro.org/
Source0: %{name}-%{version}.tar.gz

Requires: systemd
BuildRequires: systemd systemd-rpm-macros
%{?systemd_requires}

%global systemd_conf_dir %{_systemd_util_dir}/system.conf.d


%description
%{name} - %{summary} - configures platform using systemd configuration options as described by man page systemd-system.conf

# We must set debug_package to nil because there are no "source code" files to
# create debug symbols from.
%global debug_package %{nil}

%prep
%setup -n %{name}

%install
install -DpZm 644 qcom-config.conf %{buildroot}%{systemd_conf_dir}/99qcom-config.conf

%files
%{systemd_conf_dir}/99qcom-config.conf
