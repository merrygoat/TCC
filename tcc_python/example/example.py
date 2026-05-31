"""An example of how to use the TCC python wrapper to do an analysis."""
from typing import TYPE_CHECKING

from tcc_python.tcc.wrapper import TCCWrapper
import tcc_python.file_readers.xyz as xyz

if TYPE_CHECKING:
    from tcc_python.file_readers.xyz import Snapshot


def main():
    tcc_run = TCCWrapper()
    tcc_run.set_tcc_executable_directory("../../bin")
    tcc_run.input_parameters["Output"]["Raw"] = True
    snapshots: list[Snapshot] = [snap for snap in xyz.read("sample.xyz")]
    coordinates = [snap.particle_coordinates for snap in snapshots]
    tcc_run.run([27, 6.07, 21.7], coordinates)
    print(tcc_run.get_cluster_summary())


if __name__ == "__main__":
    main()
