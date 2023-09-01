### PURPOSE ###
Use this directory as place holder for DT bindings as per OOT DTBO requirements
Files in this directory are automatically included in DTC_INCLUDE Flags

### Example ###
Say, in order to include header file "foo-dt-bindings.h" in "devicetree/sa8775p_overlay.dts"
Add the file "foo-dt-bindings.h" to "devicetree/oot-dt-bindings"

In "devicetree/sa8775p_overlay.dts", include the required file as "#include <oot-dt-bindings/foo-dt-bindings.h>"
