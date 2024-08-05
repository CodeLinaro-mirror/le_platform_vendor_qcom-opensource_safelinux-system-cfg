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
%global coredump_conf_dir %{_systemd_util_dir}/coredump.conf.d


%description
Configures platform using systemd configuration options.
Also configures other systemd components such as coredump.

# We must set debug_package to nil because there are no "source code" files to
# create debug symbols from.
%global debug_package %{nil}

%prep
%setup -n %{name}

%install
install -DpZm 0644 qcom-system.conf %{buildroot}%{systemd_conf_dir}/30-qcom-system.conf
install -DpZm 0644 qcom-coredump.conf %{buildroot}%{coredump_conf_dir}/30-qcom-coredump.conf

%files
%{systemd_conf_dir}/30-qcom-system.conf
%{coredump_conf_dir}/30-qcom-coredump.conf
