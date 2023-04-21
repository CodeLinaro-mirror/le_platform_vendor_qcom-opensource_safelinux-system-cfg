Name: modules-autoload-config
Version: 1.0
Release: r0
Summary: Autoloading of dlkms during bootup
BuildArch: noarch
License: BSD-3-Clause-Clear
Source0: %{name}-%{version}.tar.gz


%description
Adding conf file to Autoload DLKMs during bootup.

%prep
%setup -qn %{name}

%install
mkdir -p  "$RPM_BUILD_ROOT/usr/lib/modules-load.d"
cp i2cdev.conf "$RPM_BUILD_ROOT/usr/lib/modules-load.d"

%files
/usr/lib/modules-load.d/i2cdev.conf
