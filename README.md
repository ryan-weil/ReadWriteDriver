# ReadWriteDriver
A kernel driver for reading and writing memory. Contains a test that writes to notepad.exe's memory, and classes to read/write to two games (Halo: MCC & Apex Legends) which are protected by EAC. I also created a modified version of ReClass.NET that utilizes the driver for its read/write operations, but the laptop I had it on sustained water damage and was destroyed. I will recreate it when I have the time.

**Please note that The function addresses are currently hardcoded for Windows 11 kernel 10.0.22000.376. A signature scanner can (and should) be added in the future to avoid this.**

![image](https://user-images.githubusercontent.com/60713027/147486318-eec99aa1-a0d5-4de1-a748-adba27aa5e2e.png)

# Technical information
 - The usermode module (ReadWriteUser.exe) loads ReadWriteDriverMapper.sys, which then manually maps ReadWriteDriver.sys
 - ReadWriteDriverMapper.sys allocates non-paged memory with `MmAllocateIndependentPages()`, and then sets its page protection to make it executable memory with `MmSetPageProtection()`
 - ReadWriteDriver.sys attaches to a usermode process that loads user32.dll (in this case, ReadWriteUser.exe) to gain access to `win32kbase.sys;NtUserSetSysColors` and overwrites a global pointer in `NtUserSetSysColors()` for its hook

# Credits
• JD96 for answering questions, of course! ☺️

• [Frostiest](https://www.unknowncheats.me/forum/anti-cheat-bypass/444289-read-process-physical-memory-attach.html) for his physmem class, since I had to add it in at the last minute after I found out that the Apex version of EAC supposedly detects `KeStackAttach()`.
