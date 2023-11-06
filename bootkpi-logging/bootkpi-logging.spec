Name: bootkpi-logging
Version: 1.0
Release: r0
Summary: bootkpi-logging API
License: BSD-3-Clause-Clear
URL: https://www.codelinaro.org/
Source0: %{name}-%{version}.tar.gz
BuildRequires: cmake gcc-c++

%description
%{name} - %{summary} - abstracts the implementation of bootkpi logging for other userspace apps.

%package devel
Summary: %{summary} - development files
Requires: %{name} = %{version}-%{release}
Requires: glibc-devel systemd-devel

%description devel
%{name} - %{summary} - development files - header and pkgconfig file

# We must set debug_package to nil because there are no "source code" files to
# create debug symbols from.
%global debug_package %{nil}

%prep
%setup -n %{name}

%build
%cmake
%cmake_build

%install
%cmake_install

%files
# Currently the main package contains no files. This may change in the future if the
# bootkpi logging implementation changes.

%files devel
%{_includedir}/bootkpi/logging.h
%{_libdir}/pkgconfig/%{name}.pc
